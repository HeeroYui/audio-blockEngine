/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>

int32_t audio::blockEngine::getLogId() {
	static int32_t g_val = elog::registerInstance("eaudiofx");
	return g_val;
}

