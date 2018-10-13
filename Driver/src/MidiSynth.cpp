/* Copyright (C) 2011, 2012 Sergey V. Mikayev
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 2.1 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"

namespace OPL3Emu {

	//#define	DRIVER_MODE

	static MidiSynth &midiSynth = MidiSynth::getInstance();
	static const unsigned int maxPos = 1024;

	static class MidiStream {
	private:
		unsigned int startpos;
		unsigned int endpos;
		DWORD stream[maxPos][2];

	public:
		MidiStream() {
			startpos = 0;
			endpos = 0;
		}

		DWORD PutMessage(DWORD msg, DWORD timestamp) {
			unsigned int newEndpos = endpos;

			newEndpos++;
			if (newEndpos == maxPos) // check for buffer rolloff
			newEndpos = 0;
			if (startpos == newEndpos) // check for buffer full
			return -1;
			stream[endpos][0] = msg;	// ok to put data and update endpos
			stream[endpos][1] = timestamp;
			endpos = newEndpos;
			return 0;
		}

		DWORD GetMessage() {
			if (startpos == endpos) // check for buffer empty
			return -1;
			DWORD msg = stream[startpos][0];
			startpos++;
			if (startpos == maxPos) // check for buffer rolloff
			startpos = 0;
			return msg;
		}

		DWORD PeekMessageTime() {
			if (startpos == endpos) // check for buffer empty
			return (DWORD)-1;
			return stream[startpos][1];
		}

		DWORD PeekMessageTimeAt(unsigned int pos) {
			if (startpos == endpos) // check for buffer empty
			return -1;
			unsigned int peekPos = (startpos + pos) % maxPos;
			return stream[peekPos][1];
		}
	} midiStream;

	static class SynthEventWin32 {
	private:
		HANDLE hEvent;

	public:
		int Init() {
			hEvent = CreateEvent(NULL, false, true, NULL);
			if (hEvent == NULL) {
				MessageBoxW(NULL, L"Can't create sync object", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
			return 0;
		}

		void Close() {
			CloseHandle(hEvent);
		}

		void Wait() {
			WaitForSingleObject(hEvent, INFINITE);
		}

		void Release() {
			SetEvent(hEvent);
		}
	} synthEvent;

	static class WaveOutWin32 {
	private:
		HWAVEOUT	hWaveOut;
		WAVEHDR		*WaveHdr;
		HANDLE		hEvent;
		DWORD		chunks;
		DWORD		prevPlayPos;
		DWORD		getPosWraps;
		bool		stopProcessing;

	public:
		int Init(Bit16s *buffer, unsigned int bufferSize, unsigned int chunkSize, bool useRingBuffer, unsigned int sampleRate) {
			char *auddev = getenv("OPL3AUDDEV");
			DWORD callbackType = CALLBACK_NULL;
			DWORD_PTR callback = NULL;
			hEvent = NULL;
			if (!useRingBuffer) {
				hEvent = CreateEvent(NULL, false, true, NULL);
				callback = (DWORD_PTR)hEvent;
				callbackType = CALLBACK_EVENT;
			}

			PCMWAVEFORMAT wFormat = {WAVE_FORMAT_PCM, 2, sampleRate, sampleRate * 4, 4, 16};

			// Open waveout device
			int wResult = waveOutOpen(&hWaveOut, WAVE_MAPPER, (LPWAVEFORMATEX)&wFormat, callback, (DWORD_PTR)&midiSynth, callbackType);
			if (auddev)
			{
				if (strstr(auddev, getenv("OPL3AUDDEV")))
				{
					wResult = waveOutOpen(&hWaveOut, atoi(auddev), (LPWAVEFORMATEX)&wFormat, callback, (DWORD_PTR)&midiSynth, callbackType);
				}
			}
			if (wResult != MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Failed to open waveform output device", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 2;
			}

			// Prepare headers
			chunks = useRingBuffer ? 1 : bufferSize / chunkSize;
			WaveHdr = new WAVEHDR[chunks];
			LPSTR chunkStart = (LPSTR)buffer;
			DWORD chunkBytes = 4 * chunkSize;
			for (UINT i = 0; i < chunks; i++) {
				if (useRingBuffer) {
					WaveHdr[i].dwBufferLength = 4 * bufferSize;
					WaveHdr[i].lpData = chunkStart;
					WaveHdr[i].dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
					WaveHdr[i].dwLoops = -1L;
				} else {
					WaveHdr[i].dwBufferLength = chunkBytes;
					WaveHdr[i].lpData = chunkStart;
					WaveHdr[i].dwFlags = 0L;
					WaveHdr[i].dwLoops = 0L;
					chunkStart += chunkBytes;
				}
				wResult = waveOutPrepareHeader(hWaveOut, &WaveHdr[i], sizeof(WAVEHDR));
				if (wResult != MMSYSERR_NOERROR) {
					MessageBoxW(NULL, L"Failed to Prepare Header", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
					return 3;
				}
			}
			stopProcessing = false;
			return 0;
		}

		int Close() {
			stopProcessing = true;
			SetEvent(hEvent);
			int wResult = waveOutReset(hWaveOut);
			if (wResult != MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Failed to Reset WaveOut", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 8;
			}

			for (UINT i = 0; i < chunks; i++) {
				wResult = waveOutUnprepareHeader(hWaveOut, &WaveHdr[i], sizeof(WAVEHDR));
				if (wResult != MMSYSERR_NOERROR) {
					MessageBoxW(NULL, L"Failed to Unprepare Wave Header", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
					return 8;
				}
			}
			delete[] WaveHdr;
			WaveHdr = NULL;

			wResult = waveOutClose(hWaveOut);
			if (wResult != MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Failed to Close WaveOut", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 8;
			}
			if (hEvent != NULL) {
				CloseHandle(hEvent);
				hEvent = NULL;
			}
			return 0;
		}

		int Start() {
			getPosWraps = 0;
			prevPlayPos = 0;
			for (UINT i = 0; i < chunks; i++) {
				if (waveOutWrite(hWaveOut, &WaveHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
					MessageBoxW(NULL, L"Failed to write block to device", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
					return 4;
				}
			}
			_beginthread(RenderingThread, 16384, this);
			return 0;
		}

		int Pause() {
			if (waveOutPause(hWaveOut) != MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Failed to Pause wave playback", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 9;
			}
			return 0;
		}

		int Resume() {
			if (waveOutRestart(hWaveOut) != MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Failed to Resume wave playback", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 9;
			}
			return 0;
		}

		UINT64 GetPos() {
			MMTIME mmTime;
			mmTime.wType = TIME_SAMPLES;

			if (waveOutGetPosition(hWaveOut, &mmTime, sizeof (MMTIME)) != MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Failed to get current playback position", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 10;
			}
			if (mmTime.wType != TIME_SAMPLES) {
				MessageBoxW(NULL, L"Failed to get # of samples played", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
				return 10;
			}

			// Deal with waveOutGetPosition() wraparound. For 16-bit stereo output, it equals 2^27,
			// presumably caused by the internal 32-bit counter of bits played.
			// The output of that nasty waveOutGetPosition() isn't monotonically increasing
			// even during 2^27 samples playback, so we have to ensure the difference is big enough...
			int delta = mmTime.u.sample - prevPlayPos;
			if (delta < -(1 << 26)) {
				std::cout << "OPL3: GetPos() wrap: " << delta << "\n";
				++getPosWraps;
			}
			prevPlayPos = mmTime.u.sample;
			return mmTime.u.sample + getPosWraps * (1 << 27);
		}

		static void RenderingThread(void *arg) {
			WaveOutWin32 *waveOut = (WaveOutWin32*)arg;
			if (waveOut->chunks == 1) {
				// Rendering using single looped ring buffer
				while (!waveOut->stopProcessing) {
					midiSynth.RenderAvailableSpace();
				}
			} else {
				while (!waveOut->stopProcessing) {
					bool allBuffersRendered = true;
					for (UINT i = 0; i < waveOut->chunks; i++) {
						if (waveOut->WaveHdr[i].dwFlags & WHDR_DONE) {
							allBuffersRendered = false;
							midiSynth.Render((Bit16s *)waveOut->WaveHdr[i].lpData, waveOut->WaveHdr[i].dwBufferLength / 4);
							if (waveOutWrite(waveOut->hWaveOut, &waveOut->WaveHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
								MessageBoxW(NULL, L"Failed to write block to device", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
							}
						}
					}
					if (allBuffersRendered) {
						WaitForSingleObject(waveOut->hEvent, INFINITE);
					}
				}
			}
		}
	} waveOut;

	MidiSynth::MidiSynth() {}

	MidiSynth &MidiSynth::getInstance() {
		static MidiSynth *instance = new MidiSynth;
		return *instance;
	}

	// Renders all the available space in the single looped ring buffer
	void MidiSynth::RenderAvailableSpace() {
		DWORD playPos = waveOut.GetPos() % bufferSize;
		DWORD framesToRender;

		if (playPos < framesRendered) {
			// Buffer wrap, render 'till the end of the buffer
			framesToRender = bufferSize - framesRendered;
		} else {
			framesToRender = playPos - framesRendered;
			if (framesToRender < chunkSize) {
				Sleep(1 + (chunkSize - framesToRender) * 1000 / sampleRate);
				return;
			}
		}
		midiSynth.Render(buffer + 2 * framesRendered, framesToRender);
	}

	// Renders totalFrames frames starting from bufpos
	// The number of frames rendered is added to the global counter framesRendered
	void MidiSynth::Render(Bit16s *bufpos, DWORD totalFrames) {
		while (totalFrames > 0) {
			DWORD timeStamp;
			// Incoming MIDI messages timestamped with the current audio playback position + midiLatency
			while ((timeStamp = midiStream.PeekMessageTime()) == framesRendered) {
				DWORD msg = midiStream.GetMessage();
				synthEvent.Wait();
				synth->midi_write(msg);
				synthEvent.Release();
			}

			// Find out how many frames to render. The value of timeStamp == -1 indicates the MIDI buffer is empty
			DWORD framesToRender = timeStamp - framesRendered;
			if (framesToRender > totalFrames) {
				// MIDI message is too far - render the rest of frames
				framesToRender = totalFrames;
			}
			synthEvent.Wait();
			synth->midi_generate(bufpos, framesToRender);
			synthEvent.Release();
			framesRendered += framesToRender;
			bufpos += 2 * framesToRender; // each frame consists of two samples for both the Left and Right channels
			totalFrames -= framesToRender;
		}

		// Wrap framesRendered counter
		if (framesRendered >= bufferSize) {
			framesRendered -= bufferSize;
		}
	}

	unsigned int MidiSynth::MillisToFrames(unsigned int millis) {
		return UINT(sampleRate * millis / 1000.f);
	}

	void MidiSynth::LoadSettings() {
		char *rate = getenv("OPL3RATE");
		char *bsize = getenv("OPL3BUFSIZE");
		char *csize = getenv("OPL3CHUNKSIZE");
		char *latency = getenv("OPL3LATENCY");
		char *ringbuf = getenv("OPL3RINGBUF");
		sampleRate = 49716;
		if (rate)
		{
			if (strstr(rate, getenv("OPL3RATE")))
			{
				sampleRate = atoi(rate);
			}
		}
		bufferSize = MillisToFrames(100);
		if (bsize)
		{
			if (strstr(bsize, getenv("OPL3BUFSIZE")))
			{
				bufferSize = MillisToFrames(atoi(bsize));
			}
		}
		chunkSize = MillisToFrames(10);
		if (csize)
		{
			if (strstr(csize, getenv("OPL3CHUNKSIZE")))
			{
				chunkSize = MillisToFrames(atoi(csize));
			}
		}
		midiLatency = MillisToFrames(0);
		if (latency)
		{
			if (strstr(latency, getenv("OPL3LATENCY")))
			{
				midiLatency = MillisToFrames(atoi(latency));
			}
		}
		useRingBuffer = false;
		if (ringbuf)
		{
			if (strstr(ringbuf, "-on"))
			{
				useRingBuffer = true;
			}
		}
		if (!useRingBuffer) {
			// Number of chunks should be ceil(bufferSize / chunkSize)
			DWORD chunks = (bufferSize + chunkSize - 1) / chunkSize;
			// Refine bufferSize as chunkSize * number of chunks, no less then the specified value
			bufferSize = chunks * chunkSize;
		}
	}

	int MidiSynth::Init() {
		LoadSettings();
		buffer = new Bit16s[2 * bufferSize]; // each frame consists of two samples for both the Left and Right channels

		// Init synth
		if (synthEvent.Init()) {
			return 1;
		}
		synth = getsynth();
		if (!synth || !synth->midi_init(sampleRate)) {
			MessageBoxW(NULL, L"Can't open Synth", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
			return 1;
		}

		UINT wResult = waveOut.Init(buffer, bufferSize, chunkSize, useRingBuffer, sampleRate);
		if (wResult) return wResult;

		// Start playing stream
		synth->midi_generate(buffer, bufferSize);
		framesRendered = 0;

		wResult = waveOut.Start();
		return wResult;
	}

	int MidiSynth::Reset() {
#ifdef DRIVER_MODE

		return 0;
#endif

		//Set a delay on reset
		char *delay = getenv("OPL3DELAY");
		if (delay)
		{
			if (strstr(delay, getenv("OPL3DELAY")))
			{
				Sleep(atoi(delay));
			}
		}
		UINT wResult = waveOut.Pause();
		if (wResult) return wResult;

		synthEvent.Wait();
		synth->midi_close();
		delete synth;
		synth = getsynth();
		if (!synth || !synth->midi_init(sampleRate)) {
			MessageBoxW(NULL, L"Can't open Synth", L"OPL3", MB_OK | MB_ICONEXCLAMATION);
			return 1;
		}
		synthEvent.Release();

		wResult = waveOut.Resume();
		return wResult;
	}

	void MidiSynth::PushMIDI(DWORD msg) {
		midiStream.PutMessage(msg, (waveOut.GetPos() + midiLatency) % bufferSize);
	}

	void MidiSynth::PlaySysex(Bit8u *bufpos, DWORD len) {
		synthEvent.Wait();
		//synth->playSysex(bufpos, len);
		synthEvent.Release();
	}

	void MidiSynth::Close() {
		//Set a delay on close
		char *delay = getenv("OPL3DELAY");
		if (delay)
		{
			if (strstr(delay, getenv("OPL3DELAY")))
			{
				Sleep(atoi(delay));
			}
		}
		waveOut.Pause();
		waveOut.Close();
		synthEvent.Wait();
		synth->midi_close();

		// Cleanup memory
		delete synth;
		delete buffer;

		synthEvent.Close();
	}

}
