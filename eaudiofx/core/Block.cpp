/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <eaudiofx/debug.hpp>
#include <eaudiofx/core/Block.hpp>
#include <eaudiofx/core/Buffer.hpp>
#include <eaudiofx/core/BlockMeta.hpp>

eaudiofx::Block::Block() {
	addObjectType("eaudiofx::Block");
}

eaudiofx::Block::~Block() {
	
}



ememory::SharedPtr<eaudiofx::Block> eaudiofx::Block::getBlockNamed(const std::string& _name) {
	ememory::SharedPtr<eaudiofx::Block> out;
	EAUDIOFX_INFO("        get block : " << _name);
	ewol::ObjectShared parrent = m_parent.lock();
	if (parrent != nullptr) {
		ememory::SharedPtr<eaudiofx::Block> parrentBlock = ememory::dynamicPointerCast<eaudiofx::Block>(parrent);
		if (parrentBlock != nullptr) {
			return parrentBlock->getBlockNamed(_name);
		} else {
			EAUDIOFX_INFO("            Parent is not a Block ...");
		}
	} else {
		EAUDIOFX_INFO("            No parent ...");
	}
	return out;
}

