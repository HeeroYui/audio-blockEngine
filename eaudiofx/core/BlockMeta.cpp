/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/core/BlockMeta.h>



eaudiofx::BlockMeta::BlockMeta(void) {
	
}

eaudiofx::BlockMeta::~BlockMeta(void) {
	// TODO : Unlink all ...
	for (auto &it : m_list) {
		if (it == NULL) {
			continue;
		}
		eaudiofx::Block* tmp = it;
		it = NULL;
		delete(tmp);
	}
	m_list.clear();
}

int32_t eaudiofx::BlockMeta::addBlock(eaudiofx::Block* _block) {
	if (_block == NULL) {
		EAUDIOFX_ERROR("[" << getUID() << "] Add NULL block");
		return eaudiofx::ERR_INPUT_NULL;
	}
	if (_block->getName().size() > 0 ) {
		// Check if name exist :
		for (auto &it : m_list) {
			if (it == NULL) {
				continue;
			}
			if (it->getName() == _block->getName()) {
				EAUDIOFX_ERROR("[" << getUID() << "] Add block name '" << _block->getName() << "' already exist");
				return eaudiofx::ERR_ALREADY_EXIST;
			}
		}
	}
	m_list.push_back(_block);
	return eaudiofx::ERR_NONE;
}

int32_t eaudiofx::BlockMeta::addBlock(const std::string& _blockType, const std::string& _name) {
	EAUDIOFX_ERROR("NOT IMPLEMENTED");
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}

int32_t eaudiofx::BlockMeta::removeBlock(const std::string& _name) {
	EAUDIOFX_ERROR("NOT IMPLEMENTED");
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}

int32_t eaudiofx::BlockMeta::replaceFilter(const std::string& _nameUnLink, const std::string& _nameLink) {
	EAUDIOFX_ERROR("NOT IMPLEMENTED");
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}

int32_t eaudiofx::BlockMeta::linkBlock(const std::string& _generatorBlockName,
                                       const std::string& _generatorIoName,
                                       const std::string& _receiverBlockName,
                                       const std::string& _receiverIoName) {
	
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}

int32_t eaudiofx::BlockMeta::openFile(const std::string& _fileName) {
	EAUDIOFX_ERROR("NOT IMPLEMENTED");
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}

int32_t eaudiofx::BlockMeta::openStream(const std::string& _stream) {
	EAUDIOFX_ERROR("NOT IMPLEMENTED");
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}

