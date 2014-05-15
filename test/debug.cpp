/**
 * @author Edouard DUPIN
 * 
 * @copyright 2010, Edouard DUPIN, all right reserved
 * 
 * @license BSD 3 clauses (see license file)
 */


#include <test/debug.h>

int32_t appl::getLogId() {
	static int32_t g_val = etk::log::registerInstance("ea-fx TT");
	return g_val;
}
