/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once


#include <etk/types.hpp>
namespace audio {
	namespace blockEngine {
		enum {
			ERR_NONE = 0,
			ERR_NOT_IMPLEMENTED,
			ERR_FAIL,
			ERR_ALREADY_EXIST,
			ERR_INPUT_NULL,
			ERR_FORBIDEN,
			ERR_NO_IO,
		};
	}
}


