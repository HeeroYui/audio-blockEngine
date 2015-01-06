/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_AUDIO_H__
#define __EAUDIOFX_AUDIO_H__


#include <etk/types.h>

namespace eaudiofx {
	enum {
		ERR_NONE = 0,
		ERR_NOT_IMPLEMENTED,
		ERR_FAIL,
		ERR_ALREADY_EXIST,
		ERR_INPUT_NULL,
		ERR_FORBIDEN,
		ERR_NO_IO,
	};
};

#endif
