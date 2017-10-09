/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/core/Block.hpp>
#include <audio/blockEngine/core/Buffer.hpp>
#include <audio/blockEngine/core/BlockMeta.hpp>

audio::blockEngine::Block::Block() {
	addObjectType("audio::blockEngine::Block");
}

audio::blockEngine::Block::~Block() {
	
}



ememory::SharedPtr<audio::blockEngine::Block> audio::blockEngine::Block::getBlockNamed(const etk::String& _name) {
	ememory::SharedPtr<audio::blockEngine::Block> out;
	ABE_INFO("        get block : " << _name);
	ewol::ObjectShared parrent = m_parent.lock();
	if (parrent != nullptr) {
		ememory::SharedPtr<audio::blockEngine::Block> parrentBlock = ememory::dynamicPointerCast<audio::blockEngine::Block>(parrent);
		if (parrentBlock != nullptr) {
			return parrentBlock->getBlockNamed(_name);
		} else {
			ABE_INFO("            Parent is not a Block ...");
		}
	} else {
		ABE_INFO("            No parent ...");
	}
	return out;
}

