
#include <stddef.h>
#include "c_types.h"

#undef OPL3EMU_EXPORT
#define OPL3EMU_EXPORT  _declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif


	/* == Context-dependent functions == */


	OPL3EMU_EXPORT opl3emu_context opl3emu_create_context(void *instance_data);

	OPL3EMU_EXPORT void opl3emu_free_context(opl3emu_context context);

	OPL3EMU_EXPORT void opl3emu_init(opl3emu_context context, int samplerate);

	OPL3EMU_EXPORT void opl3emu_writemididata(opl3emu_context context, int dwdata);

	OPL3EMU_EXPORT void opl3emu_getsample(opl3emu_context context, short *samplem, int len);

	OPL3EMU_EXPORT void opl3emu_close(opl3emu_context context);

#ifdef __cplusplus
} // extern "C"
#endif

