/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/core/Block.h>
#include <eaudiofx/core/Buffer.h>
#include <eaudiofx/core/BlockMeta.h>

#undef __class__
#define __class__ "Block"


eaudiofx::Block::Block() {
	addObjectType("eaudiofx::Block");
}

eaudiofx::Block::~Block() {
	
}



std::shared_ptr<eaudiofx::Block> eaudiofx::Block::getBlockNamed(const std::string& _name) {
	std::shared_ptr<eaudiofx::Block> out;
	EAUDIOFX_INFO("        get block : " << _name);
	std::shared_ptr<ewol::Object> parrent = m_parent.lock();
	if (parrent != nullptr) {
		std::shared_ptr<eaudiofx::Block> parrentBlock = std::dynamic_pointer_cast<eaudiofx::Block>(parrent);
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

