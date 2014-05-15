/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>

int32_t eaudiofx::getLogId() {
	static int32_t g_val = etk::log::registerInstance("eaudiofx");
	return g_val;
}

