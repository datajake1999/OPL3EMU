#include "..\interface.h"

#include "c_types.h"
#include "c_interface.h"


struct opl3emu_data {
	midisynth *synth;	
};


// C-visible implementation

extern "C" {


	opl3emu_context opl3emu_create_context(void *instance_data) {
		opl3emu_data *data = new opl3emu_data;
		data->synth = getsynth();	
		return data;
	}

	void opl3emu_free_context(opl3emu_context data) {
		if (data == NULL) return;
		delete data->synth;
		data->synth = NULL;
		delete data;
	}

	void opl3emu_init(opl3emu_context context, int samplerate) {
		if (context == NULL) return;
		context->synth->midi_init(samplerate);
	}

	void opl3emu_writemididata(opl3emu_context context, int dwdata) {
		if (context == NULL) return;
		context->synth->midi_write(dwdata);
	}

	void opl3emu_getsample(opl3emu_context context, short *samplem, int len) {
		if (context == NULL) return;
		for(unsigned int i = 0; i < len; i++)
		{
			context->synth->midi_generate(samplem, 1);
			samplem += 2;
		}
	}

	void opl3emu_close(opl3emu_context context) {
		if (context == NULL) return;
		context->synth->midi_close();
	}

	void opl3emu_boardreset(opl3emu_context context) {
		return;
	}

	void opl3emu_playsysex(opl3emu_context context, Bit8u *bufpos, DWORD len) {
		return;
	}

	void opl3emu_setpatch_sbi(opl3emu_context context, Bit8u bankNum, Bit8u patchNum, Bit8u *buf, DWORD len) {
		return;
	}

	void opl3emu_setbank(opl3emu_context context, int banknum) {
		return;
	}

	int opl3emu_getactivevoicecount(opl3emu_context context) {
		return 0;
	}

	void opl3emu_setvolume(opl3emu_context context, WORD volume_atten) {
		return;
	}

	BYTE opl3emu_getpatch(opl3emu_context context, BYTE channel) {
		return 0;
	}

	void opl3emu_usenukedopl3(opl3emu_context context, bool value) {
		return;
	}

} // extern "C"
