/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/core/BlockMeta.h>



eaudiofx::BlockMeta::BlockMeta(void) {
	
}

eaudiofx::BlockMeta::~BlockMeta(void) {
	for (auto &it : m_list) {
		if (it == NULL) {
			continue;
		}
		eaudiofx::Block* tmp = it;
		it = NULL;
		delete(tmp);
	}
}

