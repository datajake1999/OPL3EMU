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
		context->synth->midi_generate(samplem, len);
	}

	void opl3emu_close(opl3emu_context context) {
		if (context == NULL) return;
		context->synth->midi_close();
	}

} // extern "C"
