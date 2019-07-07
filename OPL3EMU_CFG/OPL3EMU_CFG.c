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
#include <conio.h>
#include <windows.h>
int main()
{
	unsigned int num;
	unsigned int apgcopy;
	unsigned int doomcopy;
	unsigned int doomcfg;
	unsigned int chips;
	unsigned int core;
	unsigned int hwconfig;
	unsigned int hwsupport;
	unsigned int hwport;
	unsigned int lptsupport;
	unsigned int lptport;
	unsigned int silence;
	unsigned int wavwrite;
	unsigned int vgmconfig;
	unsigned int vgmlog;
	unsigned int vgmloop;
	unsigned int audcfg;
	unsigned int rate;
	unsigned int bsize;
	unsigned int csize;
	unsigned int latency;
	unsigned int ringbuf;
	unsigned int auddev;
	unsigned int delay;
	unsigned int hqresampler;
	unsigned int swapstereo;
	unsigned int mono;
	unsigned int surround;
	unsigned int bitcrush;
	unsigned int crushamount;
	unsigned int dither;
	unsigned int limit;
	unsigned int reverb;
	unsigned int preset;
	unsigned int invertrev;
	unsigned int filter;
	unsigned int flttype;
	unsigned int fltfreq;
	unsigned int fltres;
	unsigned int fltgain;
	unsigned int reset;
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
		printf("10 = Themepark.\n");
		printf("11 = Wallence.\n");
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
			system("copy Apogee_TMB\\themepark.tmb c:\\OPLSynth\\apogee.tmb");
			printf("Patch copied to Apogee driver.\n");
		}
		if (apgcopy == 11)
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
		printf("10 = Daniel's GENMIDI.\n");
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
		if (doomcopy == 10)
		{
			system("copy GENMIDI\\dansgm.op2 c:\\OPLSynth\\genmidi.op2");
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
		printf("4 = Java OPL3.\n");
		printf("5 = Opal.\n");
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
		if (core == 4)
		{
			system("SetEnv -u opl3core -java");
			printf("The current OPL3 core is Java OPL3.\n");
		}
		if (core == 5)
		{
			system("SetEnv -u opl3core -opal");
			printf("The current OPL3 core is Opal.\n");
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
			printf("Enter address of FM port in Hex.\n");
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
			printf("Enter address of LPT port in Hex.\n");
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
		printf("5 = Change audio device.\n");
		printf("6 = Set delay on close.\n");
		printf("7 = Enable/disable HQ resampler.\n");
		printf("8 = Enable/disable stereo swap.\n");
		printf("9 = Enable/disable mono mixdown.\n");
		printf("10 = Configure surround sound.\n");
		printf("11 = Enable/disable bit crusher.\n");
		printf("12 = Set bit crushing amount.\n");
		printf("13 = Set dither mode.\n");
		printf("14 = Limit maximum amplitude in final output.\n");
		printf("15 = Enable/disable reverb.\n");
		printf("16 = Set reverb preset.\n");
		printf("17 = Enable/disable reverb invert.\n");
		printf("18 = Enable/disable biquad filtering.\n");
		printf("19 = Set filter type.\n");
		printf("20 = Set filter frequency.\n");
		printf("21 = Set filter resonance.\n");
		printf("22 = Set filter gain.\n");
		scanf("%d", &audcfg);
		if (audcfg == 0)
		{
			printf("Enter sample rate in Hz.\n");
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
			printf("Enter buffer size in ms.\n");
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
			printf("Enter chunk size in ms.\n");
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
			printf("Enter MIDI latency in ms.\n");
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
		if (audcfg == 6)
		{
			printf("Enter delay in ms.\n");
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
		if (audcfg == 7)
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
		if (audcfg == 8)
		{
			printf("Enable/disable stereo swap. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &swapstereo);
			if (swapstereo == 0)
			{
				system("SetEnv -u -d swapstereo");
				printf("Stereo swap has been disabled.\n");
			}
			if (swapstereo == 1)
			{
				system("SetEnv -u swapstereo -on");
				printf("Stereo swap has been enabled.\n");
			}
		}
		if (audcfg == 9)
		{
			printf("Enable/disable mono mixdown. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &mono);
			if (mono == 0)
			{
				system("SetEnv -u -d mono");
				printf("Mono mixdown has been disabled.\n");
			}
			if (mono == 1)
			{
				system("SetEnv -u mono -on");
				printf("Mono mixdown has been enabled.\n");
			}
		}
		if (audcfg == 10)
		{
			printf("Configure surround sound. Type the number that is assosiated to your desired option and press enter to apply.\n");
			printf("0 = Disable.\n");
			printf("1 = Invert left channel.\n");
			printf("2 = Invert right channel.\n");
			scanf("%d", &surround);
			if (surround == 0)
			{
				system("SetEnv -u -d surround");
				printf("Surround sound has been disabled.\n");
			}
			if (surround == 1)
			{
				system("SetEnv -u surround -left");
				printf("The left channel will be inverted.\n");
			}
			if (surround == 2)
			{
				system("SetEnv -u surround -right");
				printf("The right channel will be inverted.\n");
			}
		}
		if (audcfg == 11)
		{
			printf("Enable/disable bit crusher. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &bitcrush);
			if (bitcrush == 0)
			{
				system("SetEnv -u -d bitcrush");
				printf("Bit crusher has been disabled.\n");
			}
			if (bitcrush == 1)
			{
				system("SetEnv -u bitcrush -on");
				printf("Bit crusher has been enabled.\n");
			}
		}
		if (audcfg == 12)
		{
			printf("Enter number of bits to crush down to.\n");
			scanf("%d", &crushamount);
			if (crushamount == 8)
			{
				system("SetEnv -u -d crushamount");
			}
			else
			{
				sprintf(string, "SetEnv -u crushamount %d", crushamount);
				system(string);
			}
			printf("The bit crusher will crush the output to %d bits.\n", crushamount);
		}
		if (audcfg == 13)
		{
			printf("Set dither mode. Type the number that is assosiated to your desired dithering mode and press enter to apply.\n");
			printf("0 = None.\n");
			printf("1 = Rectangle dither.\n");
			printf("2 = Triangle dither.\n");
			printf("3 = Gaussian dither.\n");
			scanf("%d", &dither);
			if (dither == 0)
			{
				system("SetEnv -u -d dither");
				printf("No dithering is applied.\n");
			}
			if (dither == 1)
			{
				system("SetEnv -u dither -rectangle");
				printf("Rectangle dithering is applied.\n");
			}
			if (dither == 2)
			{
				system("SetEnv -u dither -triangle");
				printf("Triangle dithering is applied.\n");
			}
			if (dither == 3)
			{
				system("SetEnv -u dither -gaussian");
				printf("Gaussian dithering is applied.\n");
			}
		}
		if (audcfg == 14)
		{
			printf("Enter the maximum amplitude allowed in the final output.\n");
			scanf("%d", &limit);
			if (limit == 32767)
			{
				system("SetEnv -u -d limit");
			}
			else
			{
				sprintf(string, "SetEnv -u limit %d", limit);
				system(string);
			}
			printf("The maximum amplitude allowed in the final output is %d.\n", limit);
		}
		if (audcfg == 15)
		{
			printf("Enable/disable reverb. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &reverb);
			if (reverb == 0)
			{
				system("SetEnv -u -d reverb");
				printf("Reverb has been disabled.\n");
			}
			if (reverb == 1)
			{
				system("SetEnv -u reverb -on");
				printf("Reverb has been enabled.\n");
			}
		}
		if (audcfg == 16)
		{
			printf("Set reverb preset. Type the number that is assosiated to your desired reverb preset and press enter to apply.\n");
			printf("0 = Default.\n");
			printf("1 = Castle.\n");
			printf("2 = Stadium.\n");
			printf("3 = Heaven.\n");
			printf("4 = Sewer.\n");
			printf("5 = Psychotic.\n");
			scanf("%d", &preset);
			if (preset == 0)
			{
				system("SetEnv -u -d preset");
				printf("The default reverb preset is set.\n");
			}
			if (preset == 1)
			{
				system("SetEnv -u preset -castle");
				printf("The castle reverb preset is set.\n");
			}
			if (preset == 2)
			{
				system("SetEnv -u preset -stadium");
				printf("The stadium reverb preset is set.\n");
			}
			if (preset == 3)
			{
				system("SetEnv -u preset -heaven");
				printf("The heaven reverb preset is set.\n");
			}
			if (preset == 4)
			{
				system("SetEnv -u preset -sewer");
				printf("The sewer reverb preset is set.\n");
			}
			if (preset == 5)
			{
				system("SetEnv -u preset -psychotic");
				printf("The psychotic reverb preset is set.\n");
			}
		}
		if (audcfg == 17)
		{
			printf("Enable/disable reverb invert. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &invertrev);
			if (invertrev == 0)
			{
				system("SetEnv -u -d invertrev");
				printf("Reverb invert has been disabled.\n");
			}
			if (invertrev == 1)
			{
				system("SetEnv -u invertrev -on");
				printf("Reverb invert has been enabled.\n");
			}
		}
		if (audcfg == 18)
		{
			printf("Enable/disable biquad filtering. Press 0 to disable or 1 to enable, and press enter to apply.\n");
			scanf("%d", &filter);
			if (filter == 0)
			{
				system("SetEnv -u -d filter");
				printf("Biquad filtering has been disabled.\n");
			}
			if (filter == 1)
			{
				system("SetEnv -u filter -on");
				printf("Biquad filtering has been enabled.\n");
			}
		}
		if (audcfg == 19)
		{
			printf("Set filter type. Type the number that is assosiated to your desired filter type and press enter to apply.\n");
			printf("0 = None.\n");
			printf("1 = Lowpass.\n");
			printf("2 = Highpass.\n");
			printf("3 = Bandpass.\n");
			printf("4 = Allpass.\n");
			printf("5 = Notch.\n");
			printf("6 = Peaking.\n");
			printf("7 = Lowshelf.\n");
			printf("8 = Highshelf.\n");
			scanf("%d", &flttype);
			if (flttype == 0)
			{
				system("SetEnv -u -d flttype");
				printf("No filter is set.\n");
			}
			if (flttype == 1)
			{
				system("SetEnv -u flttype -lowpass");
				printf("Lowpass filter is set.\n");
			}
			if (flttype == 2)
			{
				system("SetEnv -u flttype -highpass");
				printf("Highpass filter is set.\n");
			}
			if (flttype == 3)
			{
				system("SetEnv -u flttype -bandpass");
				printf("Bandpass filter is set.\n");
			}
			if (flttype == 4)
			{
				system("SetEnv -u flttype -allpass");
				printf("Allpass filter is set.\n");
			}
			if (flttype == 5)
			{
				system("SetEnv -u flttype -notch");
				printf("Notch filter is set.\n");
			}
			if (flttype == 6)
			{
				system("SetEnv -u flttype -peaking");
				printf("Peaking filter is set.\n");
			}
			if (flttype == 7)
			{
				system("SetEnv -u flttype -lowshelf");
				printf("Lowshelf filter is set.\n");
			}
			if (flttype == 8)
			{
				system("SetEnv -u flttype -highshelf");
				printf("Highshelf filter is set.\n");
			}
		}
		if (audcfg == 20)
		{
			printf("Enter frequency.\n");
			scanf("%d", &fltfreq);
			if (fltfreq == 0)
			{
				system("SetEnv -u -d fltfreq");
			}
			else
			{
				sprintf(string, "SetEnv -u fltfreq %d", fltfreq);
				system(string);
			}
			printf("The filter frequency has been set to %d.\n", fltfreq);
		}
		if (audcfg == 21)
		{
			printf("Enter resonance.\n");
			scanf("%d", &fltres);
			if (fltres == 0)
			{
				system("SetEnv -u -d fltres");
			}
			else
			{
				sprintf(string, "SetEnv -u fltres %d", fltres);
				system(string);
			}
			printf("The filter resonance has been set to %d.\n", fltres);
		}
		if (audcfg == 22)
		{
			printf("Enter gain.\n");
			scanf("%d", &fltgain);
			if (fltgain == 0)
			{
				system("SetEnv -u -d fltgain");
			}
			else
			{
				sprintf(string, "SetEnv -u fltgain %d", fltgain);
				system(string);
			}
			printf("The filter gain has been set to %d.\n", fltgain);
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
		char *auddev = getenv("OPL3AUDDEV");
		char *delay = getenv("OPL3DELAY");
		char *hqresampler = getenv("HQRESAMPLER");
		char *swapstereo = getenv("SWAPSTEREO");
		char *mono = getenv("MONO");
		char *surround = getenv("SURROUND");
		char *bitcrush = getenv("BITCRUSH");
		char *crushamount = getenv("CRUSHAMOUNT");
		char *dither = getenv("DITHER");
		char *limit = getenv("LIMIT");
		char *reverb = getenv("REVERB");
		char *preset = getenv("PRESET");
		char *invertrev = getenv("INVERTREV");
		char *filter = getenv("FILTER");
		char *flttype = getenv("FLTTYPE");
		char *fltfreq = getenv("FLTFREQ");
		char *fltres = getenv("FLTRES");
		char *fltgain = getenv("FLTGAIN");
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
			if (strstr(core, "-java"))
			{
				printf("Java OPL3 is the current OPL3 core.\n");
			}
			if (strstr(core, "-opal"))
			{
				printf("Opal is the current OPL3 core.\n");
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
					printf("The current FM port is %s.\n", hwport);
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
					printf("The current LPT port is %s.\n", lptport);
				}
				else
				{
					printf("The current LPT port is 378.\n");
				}
				if (opl2lptmode)
				{
					if (strstr(opl2lptmode, "-on"))
					{
						printf("The LPT driver is in OPL2LPT mode.\n");
					}
				}
				else
				{
					printf("The LPT driver is in OPL3LPT mode.\n");
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
			printf("The current sample rate is %s.\n", rate);
		}
		else
		{
			printf("The current sample rate is 49716.\n");
		}
		if (bsize)
		{
			printf("The current buffer size is %s.\n", bsize);
		}
		else
		{
			printf("The current buffer size is 100.\n");
		}
		if (csize)
		{
			printf("The current chunk size is %s.\n", csize);
		}
		else
		{
			printf("The current chunk size is 10.\n");
		}
		if (latency)
		{
			printf("The current MIDI latency is %s.\n", latency);
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
		if (auddev)
		{
			printf("The driver sends output to the audio device with id%s.\n", auddev);
		}
		else
		{
			printf("The driver sends output to the default audio device.\n");
		}
		if (delay)
		{
			printf("The driver will close after %s ms.\n", delay);
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
		if (swapstereo)
		{
			if (strstr(swapstereo, "-on"))
			{
				printf("Stereo swap is enabled.\n");
			}
		}
		else
		{
			printf("Stereo swap is disabled.\n");
		}
		if (mono)
		{
			if (strstr(mono, "-on"))
			{
				printf("Mono mixdown is enabled.\n");
			}
		}
		else
		{
			printf("Mono mixdown is disabled.\n");
		}
		if (surround)
		{
			if (strstr(surround, "-left"))
			{
				printf("The left channel is inverted.\n");
			}
			if (strstr(surround, "-right"))
			{
				printf("The right channel is inverted.\n");
			}
		}
		else
		{
			printf("Surround sound is disabled.\n");
		}
		if (bitcrush)
		{
			if (strstr(bitcrush, "-on"))
			{
				printf("Bit crusher is enabled.\n");
				if (crushamount)
				{
					printf("The bit crusher crushes the output to %s bits.\n", crushamount);
				}
				else
				{
					printf("The bit crusher crushes the output to 8 bits.\n");
				}
				if (dither)
				{
					if (strstr(dither, "-rectangle"))
					{
						printf("Rectangle dithering is applied.\n");
					}
					if (strstr(dither, "-triangle"))
					{
						printf("Triangle dithering is applied.\n");
					}
					if (strstr(dither, "-gaussian"))
					{
						printf("Gaussian dithering is applied.\n");
					}
				}
				else
				{
					printf("No dithering is applied.\n");
				}
			}
		}
		else
		{
			printf("Bit crusher is disabled.\n");
		}
		if (limit)
		{
			printf("The maximum amplitude allowed in the final output is %s.\n", limit);
		}
		if (reverb)
		{
			if (strstr(reverb, "-on"))
			{
				printf("Reverb is enabled.\n");
				if (preset)
				{
					if (strstr(preset, "-castle"))
					{
						printf("The castle preset is set.\n");
					}
					if (strstr(preset, "-stadium"))
					{
						printf("The stadium preset is set.\n");
					}
					if (strstr(preset, "-heaven"))
					{
						printf("The heaven preset is set.\n");
					}
					if (strstr(preset, "-sewer"))
					{
						printf("The sewer preset is set.\n");
					}
					if (strstr(preset, "-psychotic"))
					{
						printf("The psychotic preset is set.\n");
					}
				}
				else
				{
					printf("The default preset is set.\n");
				}
				if (invertrev)
				{
					if (strstr(invertrev, "-on"))
					{
						printf("Reverb invert is enabled.\n");
					}
				}
			}
		}
		else
		{
			printf("Reverb is disabled.\n");
		}
		if (filter)
		{
			if (strstr(filter, "-on"))
			{
				printf("Biquad filtering is enabled.\n");
				if (flttype)
				{
					if (strstr(flttype, "-lowpass"))
					{
						printf("Lowpass filter is applied.\n");
					}
					if (strstr(flttype, "-highpass"))
					{
						printf("Highpass filter is applied.\n");
					}
					if (strstr(flttype, "-bandpass"))
					{
						printf("Bandpass filter is applied.\n");
					}
					if (strstr(flttype, "-allpass"))
					{
						printf("Allpass filter is applied.\n");
					}
					if (strstr(flttype, "-notch"))
					{
						printf("Notch filter is applied.\n");
					}
					if (strstr(flttype, "-peaking"))
					{
						printf("Peaking filter is applied.\n");
					}
					if (strstr(flttype, "-lowshelf"))
					{
						printf("Lowshelf filter is applied.\n");
					}
					if (strstr(flttype, "-highshelf"))
					{
						printf("Highshelf filter is applied.\n");
					}
				}
				if (fltfreq)
				{
					printf("The filter frequency is %s.\n", fltfreq);
				}
				if (fltres)
				{
					printf("The filter resonance is %s.\n", fltres);
				}
				if (fltgain)
				{
					printf("The filter gain is %s.\n", fltgain);
				}
			}
		}
		else
		{
			printf("Biquad filtering is disabled.\n");
		}
		printf("Press any key to exit.\n");
		getch();
	}
	if (num == 9)
	{
		printf("Reset driver configuration. Press 1 to reset, or 0 to cancel.\n");
		scanf("%d", &reset);
		if(reset == 0)
		{
			printf("Driver configuration hasn't been reset.\n");
		}
		if(reset == 1)
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
			system("SetEnv -u -d opl3auddev");
			system("SetEnv -u -d opl3delay");
			system("SetEnv -u -d hqresampler");
			system("SetEnv -u -d swapstereo");
			system("SetEnv -u -d mono");
			system("SetEnv -u -d surround");
			system("SetEnv -u -d bitcrush");
			system("SetEnv -u -d crushamount");
			system("SetEnv -u -d dither");
			system("SetEnv -u -d limit");
			system("SetEnv -u -d reverb");
			system("SetEnv -u -d preset");
			system("SetEnv -u -d invertrev");
			system("SetEnv -u -d filter");
			system("SetEnv -u -d flttype");
			system("SetEnv -u -d fltfreq");
			system("SetEnv -u -d fltres");
			system("SetEnv -u -d fltgain");
			printf("Driver configuration has been reset.\n");
		}
		printf("Press any key to exit.\n");
		getch();
	}
	printf("Exiting.\n");
	return 0;
}
