/*
OPL3EMU MIDI driver configuration utility
Copyright (C) 2017-2018 Datajake

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <stdio.h>
#include <windows.h>
int main()
{
	int num;
	int apgcopy;
	int doomcopy;
	int doomcfg;
	int chips;
	int core;
	int hwconfig;
	int hwsupport;
	int hwport;
	int lptsupport;
	int lptport;
	int silence;
	int wavwrite;
	int vgmconfig;
	int vgmlog;
	int vgmloop;
	int audcfg;
	int rate;
	int bsize;
	int csize;
	int latency;
	int ringbuf;
	int hqresampler;
	int auddev;
	int delay;
	char string[100];
	CreateDirectory("C:\\OPLSynth", NULL);
	printf("OPL3EMU MIDI driver configuration utility. Type the number that is assosiated to what you want to configure and press enter to continue.\n");
	printf("0 = Copy patch to Apogee driver.\n");
	printf("1 = Copy patch to Doom driver.\n");
	printf("2 = Configure Doom driver.\n");
	printf("3 = Select OPL3 core.\n");
	printf("4 = Configure Hardware OPL passthrough.\n");
	printf("5 = Enable/disable WAV file writing.\n");
	printf("6 = Configure VGM logging.\n");
	printf("7 = Audio configuration.\n");
	printf("8 = Read current driver configuration.\n");
	printf("9 = Reset driver configuration.\n");
	scanf("%d", &num);
	if (num == 0)
	{
		printf("Copy patch to Apogee driver. Type the number that is assosiated to your desired patch set and press enter to copy.\n");
		printf("0 = ROTT 1.3, Build engine games setup utility.\n");
		printf("1 = Blood.\n");
		printf("2 = Duke Nukem 3D.\n");
		printf("3 = ROTT 1.0-1.2.\n");
		printf("4 = NAM.\n");
		printf("5 = Shadow Warrior(Shareware).\n");
		printf("6 = Cyberpuck.\n");
		printf("7 = Drumopl.\n");
		printf("8 = Gmoconel.\n");
		printf("9 = Gmoplmod.\n");
		printf("10 = Wallence.\n");
		scanf("%d", &apgcopy);
		if (apgcopy == 0)
		{
			system("del c:\\OPLSynth\\apogee.tmb");
			printf("The Apogee driver is now configured to use the built in patch set.\n");
		}
		if (apgcopy == 1)
		{
			system("copy Apogee_TMB\\apogee_blood.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 2)
		{
			system("copy Apogee_TMB\\apogee_duke3d.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 3)
		{
			system("copy Apogee_TMB\\apogee_lee.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 4)
		{
			system("copy Apogee_TMB\\apogee_nam.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 5)
		{
			system("copy Apogee_TMB\\apogee_sw.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 6)
		{
			system("copy Apogee_TMB\\cyberpuck.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 7)
		{
			system("copy Apogee_TMB\\drumopl.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 8)
		{
			system("copy Apogee_TMB\\gmoconel.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 9)
		{
			system("copy Apogee_TMB\\gmoplmod.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 10)
		{
			system("copy Apogee_TMB\\wallence.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 1)
	{
		printf("Copy Patch to Doom driver. Type the number that is assosiated to your desired patch set and press enter to copy.\n");
		printf("0 = DMX, Heretic, Hexen, Doom Beta, Strife Demo.\n");
		printf("1 = Doom, Ultimate Doom, Chex Quest.\n");
		printf("2 = Doom II, Final Doom.\n");
		printf("3 = Strife.\n");
		printf("4 = Raptor.\n");
		printf("5 = Wolfinstein 3D.\n");
		printf("6 = DMXOPL by Sneakernets.\n");
		printf("7 = GENMID01 by Dan L'Ecuyer.\n");
		printf("8 = Hisymak's GENMIDI.\n");
		printf("9 = Freedoom.\n");
		scanf("%d", &doomcopy);
		if (doomcopy == 0)
		{
			system("copy GENMIDI\\dmx_dmx.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 1)
		{
			system("copy GENMIDI\\dmx_doom1.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 2)
		{
			system("copy GENMIDI\\dmx_doom2.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 3)
		{
			system("copy GENMIDI\\dmx_strife.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 4)
		{
			system("copy GENMIDI\\dmx_raptor.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 5)
		{
			system("copy GENMIDI\\wolfinstein.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 6)
		{
			system("copy GENMIDI\\dmxopl.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 7)
		{
			system("copy GENMIDI\\genmid01.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 8)
		{
			system("copy GENMIDI\\hisymak.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		if (doomcopy == 9)
		{
			system("copy GENMIDI\\freedoom.op2 c:\\OPLSynth\\genmidi.op2");
			printf("Patch copied to Doom driver.\n");
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 2)
	{
		printf("Configure Doom driver. Type the number that is assosiated to your desired configuration and press enter to apply.\n");
		printf("0 = Default.\n");
		printf("1 = Doom1.\n");
		printf("2 = Doom2.\n");
		printf("3 = OPL3 mode.\n");
		printf("4 = Doom1 (OPL3 mode).\n");
		printf("5 = Doom2 (OPL3 mode).\n");
		printf("6 = OPL3 mode, with full stereo panpot.\n");
		printf("7 = Doom1 (OPL3 mode, with full stereo panpot).\n");
		printf("8 = Doom2 (OPL3 mode, with full stereo panpot).\n");
		scanf("%d", &doomcfg);
		if (doomcfg == 0)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -chips~chips~");
			printf("Default configuration set.\n");
		}
		if (doomcfg == 1)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -doom1-chips~chips~");
			printf("Doom1 configuration set.\n");
		}
		if (doomcfg == 2)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -doom2-chips~chips~");
			printf("Doom2 configuration set.\n");
		}
		if (doomcfg == 3)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -opl3-chips~chips~");
			printf("OPL3 mode configuration set.\n");
		}
		if (doomcfg == 4)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -doom1-opl3-chips~chips~");
			printf("Doom1 (OPL3 mode) configuration set.\n");
		}
		if (doomcfg == 5)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -doom2-opl3-chips~chips~");
			printf("Doom2 (OPL3 mode) configuration set.\n");
		}
		if (doomcfg == 6)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -opl3-extstereo-chips~chips~");
			printf("OPL3 mode, with full stereo panpot configuration set.\n");
		}
		if (doomcfg == 7)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -doom1-opl3-extstereo-chips~chips~");
			printf("Doom1 (OPL3 mode, with full stereo panpot) configuration set.\n");
		}
		if (doomcfg == 8)
		{
			system("SetEnv -u -d dmxoption");
			system("SetEnv -u dmxoption -doom2-opl3-extstereo-chips~chips~");
			printf("Doom2 (OPL3 mode, with full stereo panpot) configuration set.\n");
		}
		printf("How many emulated chips?");
		scanf("%d", &chips);
		if (chips == 1)
		{
			system("SetEnv -u chips 1");
			printf("1 Chip set.\n");
		}
		if (chips == 2)
		{
			system("SetEnv -u chips 2");
			printf("2 Chips set.\n");
		}
		if (chips == 3)
		{
			system("SetEnv -u chips 3");
			printf("3 Chips set.\n");
		}
		if (chips == 4)
		{
			system("SetEnv -u chips 4");
			printf("4 Chips set.\n");
		}
		if (chips == 5)
		{
			system("SetEnv -u chips 5");
			printf("5 Chips set.\n");
		}
		if (chips == 6)
		{
			system("SetEnv -u chips 6");
			printf("6 Chips set.\n");
		}
		if (chips == 7)
		{
			system("SetEnv -u chips 7");
			printf("7 Chips set.\n");
		}
		if (chips == 8)
		{
			system("SetEnv -u chips 8");
			printf("8 Chips set.\n");
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 3)
	{
		printf("Select OPL3 core. Type the number that is assosiated to your desired OPL3 Emulator Core and press enter to apply.\n");
		printf("0 = Nuked.\n");
		printf("1 = DOSBox compat.\n");
		printf("2 = DOSBox fast.\n");
		printf("3 = MAME.\n");
		scanf("%d", &core);
		if (core == 0)
		{
			system("SetEnv -u -d opl3core");
			printf("The current OPL3 core is Nuked.\n");
		}
		if (core == 1)
		{
			system("SetEnv -u opl3core -dbcompat");
			printf("The current OPL3 core is DOSBox compat.\n");
		}
		if (core == 2)
		{
			system("SetEnv -u opl3core -dbfast");
			printf("The current OPL3 core is DOSBox fast.\n");
		}
		if (core == 3)
		{
			system("SetEnv -u opl3core -mame");
			printf("The current OPL3 core is MAME.\n");
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 4)
	{
		printf("Hardware OPL passthrough configuration.\n");
		printf("0 = Enable/disable Hardware OPL passthrough.\n");
		printf("1 = Set FM port.\n");
		printf("2 = Enable/disable OPL3LPT mode.\n");
		printf("3 = Set LPT port.\n");
		printf("4 = Enable/disable Silent emulation mode.\n");
		scanf("%d", &hwconfig);
		if (hwconfig == 0)
		{
			printf("Enable/disable Hardware OPL passthrough. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &hwsupport);
			if (hwsupport == 0)
			{
				system("SetEnv -u -d oplhwsupport");
				printf("Hardware OPL passthrough has been disabled.\n");
			}
			if (hwsupport == 1)
			{
				system("SetEnv -u oplhwsupport -on");
				printf("Hardware OPL passthrough has been enabled.\n");
			}
		}
		if (hwconfig == 1)
		{
			printf("Enter address of FM port.\n");
			scanf("%x", &hwport);
			if (hwport == 0x388)
			{
				system("SetEnv -u -d opl3port");
			}
			else
			{
				sprintf(string, "SetEnv -u opl3port %x", hwport);
				system(string);
			}
			printf("The FM port has been set to %x.\n", hwport);
		}
		if (hwconfig == 2)
		{
			printf("Enable/disable OPL3LPT mode. Press 0 to disable or 1 to enable, and press enter to apply. Note: if you have an OPL2LPT, you can press 2 to tell the LPT driver to go into OPL2LPT mode. Press 3 to disable OPL2LPT mode.\n");
			scanf("%d", &lptsupport);
			if (lptsupport == 0)
			{
				system("SetEnv -u -d oplhwsupport");
				printf("OPL3LPT mode has been disabled.\n");
			}
			if (lptsupport == 1)
			{
				system("SetEnv -u oplhwsupport -lpt");
				printf("OPL3LPT mode has been enabled.\n");
			}
			if (lptsupport == 2)
			{
				system("SetEnv -u opl2lptmode -on");
				printf("OPL2LPT mode has been enabled.\n");
			}
			if (lptsupport == 3)
			{
				system("SetEnv -u -d opl2lptmode");
				printf("OPL2LPT mode has been disabled.\n");
			}
		}
		if (hwconfig == 3)
		{
			printf("Enter address of LPT port.\n");
			scanf("%x", &lptport);
			if (lptport == 0x378)
			{
				system("SetEnv -u -d lptport");
			}
			else
			{
				sprintf(string, "SetEnv -u lptport %x", lptport);
				system(string);
			}
			printf("The LPT port has been set to %x.\n", lptport);
		}
		if (hwconfig == 4)
		{
			printf("Enable/disable silent emulation mode. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &silence);
			if (silence == 0)
			{
				system("SetEnv -u -d oplemusilence");
				printf("Silent emulation mode has been disabled.\n");
			}
			if (silence == 1)
			{
				system("SetEnv -u oplemusilence -on");
				printf("Silent emulation mode has been enabled.\n");
			}
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 5)
	{
		printf("Enable/disable WAV file writing. Press 0 to disable or 1 to enable, and press enter to apply.\n");
		scanf("%d", &wavwrite);
		if (wavwrite == 0)
		{
			system("SetEnv -u -d wavwrite");
			printf("WAV file writing has been disabled.\n");
		}
		if (wavwrite == 1)
		{
			system("SetEnv -u wavwrite -on");
			printf("WAV file writing has been enabled. The audio output of the emulator is stored in C:\\OPLSynth\\output.wav.\n");
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 6)
	{
		printf("VGM logging configuration.\n");
		printf("0 = Enable/disable VGM logging.\n");
		printf("1 = Enable/disable VGM looping.\n");
		scanf("%d", &vgmconfig);
		if (vgmconfig == 0)
		{
			printf("Enable/disable VGM logging. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &vgmlog);
			if (vgmlog == 0)
			{
				system("SetEnv -u -d vgmlog");
				printf("VGM logging has been disabled.\n");
			}
			if (vgmlog == 1)
			{
				system("SetEnv -u vgmlog -on");
				printf("VGM logging has been enabled. The log is stored in C:\\OPLSynth\\opl3vgmlog.vgm.\n");
			}
		}
		if (vgmconfig == 1)
		{
			printf("Enable/disable VGM looping. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &vgmloop);
			if (vgmloop == 0)
			{
				system("SetEnv -u -d vgmloop");
				printf("VGM looping has been disabled.\n");
			}
			if (vgmloop == 1)
			{
				system("SetEnv -u vgmloop -on");
				printf("VGM looping has been enabled. A VGM loop Start marker will be placed at the beginning of the Resulting VGM file.\n");
			}
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 7)
	{
		printf("Audio configuration.\n");
		printf("0 = Change sample rate.\n");
		printf("1 = Change buffer size.\n");
		printf("2 = Change chunk size.\n");
		printf("3 = Change MIDI latency.\n");
		printf("4 = Enable/disable ring buffer.\n");
		printf("5 = Enable/disable HQ resampler.\n");
		printf("6 = Change audio device.\n");
		printf("7 = Set delay on close.\n");
		scanf("%d", &audcfg);
		if (audcfg == 0)
		{
			printf("Enter sample rate in HZ.\n");
			scanf("%d", &rate);
			if (rate == 49716)
			{
				system("SetEnv -u -d opl3rate");
			}
			else
			{
				sprintf(string, "SetEnv -u opl3rate %d", rate);
				system(string);
			}
			printf("The sample rate has been set to %d.\n", rate);
		}
		if (audcfg == 1)
		{
			printf("Enter buffer size in MS.\n");
			scanf("%d", &bsize);
			if (bsize == 100)
			{
				system("SetEnv -u -d opl3bufsize");
			}
			else
			{
				sprintf(string, "SetEnv -u opl3bufsize %d", bsize);
				system(string);
			}
			printf("The buffer size has been set to %d.\n", bsize);
		}
		if (audcfg == 2)
		{
			printf("Enter chunk size in MS.\n");
			scanf("%d", &csize);
			if (csize == 10)
			{
				system("SetEnv -u -d opl3chunksize");
			}
			else
			{
				sprintf(string, "SetEnv -u opl3chunksize %d", csize);
				system(string);
			}
			printf("The chunk size has been set to %d.\n", csize);
		}
		if (audcfg == 3)
		{
			printf("Enter MIDI latency in MS.\n");
			scanf("%d", &latency);
			if (latency == 0)
			{
				system("SetEnv -u -d opl3latency");
			}
			else
			{
				sprintf(string, "SetEnv -u opl3latency %d", latency);
				system(string);
			}
			printf("The MIDI latency has been set to %d.\n", latency);
		}
		if (audcfg == 4)
		{
			printf("Enable/disable ring buffer. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &ringbuf);
			if (ringbuf == 0)
			{
				system("SetEnv -u -d opl3ringbuf");
				printf("Ring buffer has been disabled.\n");
			}
			if (ringbuf == 1)
			{
				system("SetEnv -u opl3ringbuf -on");
				printf("Ring buffer has been enabled.\n");
			}
		}
		if (audcfg == 5)
		{
			printf("Enable/disable HQ resampler. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &hqresampler);
			if (hqresampler == 0)
			{
				system("SetEnv -u -d hqresampler");
				printf("HQ resampler has been disabled.\n");
			}
			if (hqresampler == 1)
			{
				system("SetEnv -u hqresampler -on");
				printf("HQ resampler has been enabled.\n");
			}
		}
		if (audcfg == 6)
		{
			printf("Enter device ID.\n");
			scanf("%d", &auddev);
			if (auddev == -1)
			{
				system("SetEnv -u -d opl3auddev");
				printf("The driver will send output to the default audio device.\n");
			}
			else
			{
				sprintf(string, "SetEnv -u opl3auddev %d", auddev);
				system(string);
				printf("The driver will send output to the audio device with id %d.\n", auddev);
			}
		}
		if (audcfg == 7)
		{
			printf("Enter delay in MS.\n");
			scanf("%d", &delay);
			if (delay == 0)
			{
				system("SetEnv -u -d opl3delay");
			}
			else
			{
				sprintf(string, "SetEnv -u opl3delay %d", delay);
				system(string);
			}
			printf("The delay on close has been set to %d.\n", delay);
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 8)
	{
		char *core = getenv("OPL3CORE");
		char *hwsupport = getenv("OPLHWSUPPORT");
		char *hwport = getenv("OPL3PORT");
		char *lptport = getenv("LPTPORT");
		char *opl2lptmode = getenv("OPL2LPTMODE");
		char *silence = getenv("OPLEMUSILENCE");
		char *wavwrite = getenv("WAVWRITE");
		char *vgmlog = getenv("VGMLOG");
		char *vgmloop = getenv("VGMLOOP");
		char *env = getenv("DMXOPTION");
		char *chips = getenv("CHIPS");
		char *rate = getenv("OPL3RATE");
		char *bsize = getenv("OPL3BUFSIZE");
		char *csize = getenv("OPL3CHUNKSIZE");
		char *latency = getenv("OPL3LATENCY");
		char *ringbuf = getenv("OPL3RINGBUF");
		char *hqresampler = getenv("HQRESAMPLER");
		char *auddev = getenv("OPL3AUDDEV");
		char *delay = getenv("OPL3DELAY");
		printf("General driver configuration.\n");
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				printf("DOSBox compat is the current OPL3 core.\n");
			}
			if (strstr(core, "-dbfast"))
			{
				printf("DOSBox fast is the current OPL3 core.\n");
			}
			if (strstr(core, "-mame"))
			{
				printf("MAME is the current OPL3 core.\n");
			}
		}
		else
		{
			printf("Nuked is the current OPL3 core.\n");
		}
		if (hwsupport)
		{
			if (strstr(hwsupport, "-on"))
			{
				printf("Hardware OPL passthrough is enabled.\n");
				if (hwport)
				{
					if (strstr(hwport, getenv("OPL3PORT")))
					{
						printf("The current FM port is %s.\n", hwport);
					}
				}
				else
				{
					printf("The current FM port is 388.\n");
				}
			}
			if (strstr(hwsupport, "-lpt"))
			{
				printf("OPL3LPT mode is enabled.\n");
				if (lptport)
				{
					if (strstr(lptport, getenv("LPTPORT")))
					{
						printf("The current LPT port is %s.\n", lptport);
					}
				}
				else
				{
					printf("The current LPT port is 378.\n");
				}
				if (opl2lptmode)
				{
					if (strstr(opl2lptmode, "-on"))
					{
						printf("The LPT driver  is in OPL2LPT mode.\n");
					}
				}
			}
		}
		else
		{
			printf("Hardware OPL passthrough is disabled.\n");
		}
		if (silence)
		{
			if (strstr(silence, "-on"))
			{
				printf("Silent emulation mode is enabled.\n");
			}
		}
		else
		{
			printf("Silent emulation mode is disabled.\n");
		}
		if (wavwrite)
		{
			if (strstr(wavwrite, "-on"))
			{
				printf("WAV file writing is enabled.\n");
			}
		}
		else
		{
			printf("WAV file writing is disabled.\n");
		}
		if (vgmlog)
		{
			if (strstr(vgmlog, "-on"))
			{
				printf("VGM logging is enabled.\n");
				if (vgmloop)
				{
					if (strstr(vgmloop, "-on"))
					{
						printf("VGM looping is enabled.\n");
					}
				}
				else
				{
					printf("VGM looping is disabled.\n");
				}
			}
		}
		else
		{
			printf("VGM logging is disabled.\n");
		}
		printf("Doom driver configuration.\n");
		if (env)
		{
			if (strstr(env, "-opl3"))
			{
				printf("OPL3 mode is enabled.\n");
			}
			if (strstr(env, "-extstereo"))
			{
				printf("Full stereo panpot is enabled.\n");
			}
			if (strstr(env, "-doom1"))
			{
				printf("Doom1 configuration is set.\n");
			}
			if (strstr(env, "-doom2"))
			{
				printf("Doom2 configuration is set.\n");
			}
		}
		if (chips)
		{
			if (strstr(chips, "1"))
			{
				printf("1 Chip is emulated.\n");
			}
			if (strstr(chips, "2"))
			{
				printf("2 Chips are emulated.\n");
			}
			if (strstr(chips, "3"))
			{
				printf("3 Chips are emulated.\n");
			}
			if (strstr(chips, "4"))
			{
				printf("4 Chips are emulated.\n");
			}
			if (strstr(chips, "5"))
			{
				printf("5 Chips are emulated.\n");
			}
			if (strstr(chips, "6"))
			{
				printf("6 Chips are emulated.\n");
			}
			if (strstr(chips, "7"))
			{
				printf("7 Chips are emulated.\n");
			}
			if (strstr(chips, "8"))
			{
				printf("8 Chips are emulated.\n");
			}
		}
		printf("Driver audio configuration.\n");
		if (rate)
		{
			if (strstr(rate, getenv("OPL3RATE")))
			{
				printf("The current sample rate is %s.\n", rate);
			}
		}
		else
		{
			printf("The current sample rate is 49716.\n");
		}
		if (bsize)
		{
			if (strstr(bsize, getenv("OPL3BUFSIZE")))
			{
				printf("The current buffer size is %s.\n", bsize);
			}
		}
		else
		{
			printf("The current buffer size is 100.\n");
		}
		if (csize)
		{
			if (strstr(csize, getenv("OPL3CHUNKSIZE")))
			{
				printf("The current chunk size is %s.\n", csize);
			}
		}
		else
		{
			printf("The current chunk size is 10.\n");
		}
		if (latency)
		{
			if (strstr(latency, getenv("OPL3LATENCY")))
			{
				printf("The current MIDI latency is %s.\n", latency);
			}
		}
		else
		{
			printf("The current MIDI latency is 0.\n");
		}
		if (ringbuf)
		{
			if (strstr(ringbuf, "-on"))
			{
				printf("The ring buffer is enabled.\n");
			}
		}
		else
		{
			printf("The ring buffer is disabled.\n");
		}
		if (hqresampler)
		{
			if (strstr(hqresampler, "-on"))
			{
				printf("The HQ resampler is enabled.\n");
			}
		}
		else
		{
			printf("The HQ resampler is disabled.\n");
		}
		if (auddev)
		{
			if (strstr(auddev, getenv("OPL3AUDDEV")))
			{
				printf("The driver sends output to the audio device with id%s.\n", auddev);
			}
		}
		else
		{
			printf("The driver sends output to the default audio device.\n");
		}
		if (delay)
		{
			if (strstr(delay, getenv("OPL3DELAY")))
			{
				printf("The driver will close after %s MS.\n", delay);
			}
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 9)
	{
		system("del c:\\OPLSynth\\apogee.tmb");
		system("copy GENMIDI\\dmx_dmx.op2 c:\\OPLSynth\\genmidi.op2");
		system("SetEnv -u -d dmxoption");
		system("SetEnv -u -d chips");
		system("SetEnv -u -d opl3core");
		system("SetEnv -u -d oplhwsupport");
		system("SetEnv -u -d opl3port");
		system("SetEnv -u -d lptport");
		system("SetEnv -u -d opl2lptmode");
		system("SetEnv -u -d oplemusilence");
		system("SetEnv -u -d wavwrite");
		system("SetEnv -u -d vgmlog");
		system("SetEnv -u -d vgmloop");
		system("SetEnv -u -d opl3rate");
		system("SetEnv -u -d opl3bufsize");
		system("SetEnv -u -d opl3chunksize");
		system("SetEnv -u -d opl3latency");
		system("SetEnv -u -d opl3ringbuf");
		system("SetEnv -u -d hqresampler");
		system("SetEnv -u -d opl3auddev");
		system("SetEnv -u -d opl3delay");
		printf("Driver configuration has been reset.\n");
		printf("Press any key to exit.\n");
		getch();
	}
	printf("Exiting.\n");
	return 0;
}
