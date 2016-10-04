/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */


#include <test/debug.hpp>

int32_t appl::getLogId() {
	static int32_t g_val = elog::registerInstance("ea-fx TT");
	return g_val;
}
