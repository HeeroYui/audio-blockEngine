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

void eaudiofx::BlockMeta::addBlock(eaudiofx::Block* _block) {
	if (_block == NULL) {
		throw eaudiofx::exeption::StdExeption(std::string("[") + std::to_string(getUID()) + "] Add NULL block");
	}
	if (_block->getName().size() > 0 ) {
		// Check if name exist :
		for (auto &it : m_list) {
			if (it == NULL) {
				continue;
			}
			if (it->getName() == _block->getName()) {
				throw eaudiofx::exeption::StdExeption(std::string("[") + std::to_string(getUID()) + "] Add block name '" + _block->getName() + "' already exist");
			}
		}
	}
	m_list.push_back(_block);
}

void eaudiofx::BlockMeta::addBlock(const std::string& _blockType, const std::string& _name) {
	throw eaudiofx::exeption::StdExeption("NOT IMPLEMENTED");
}

void eaudiofx::BlockMeta::removeBlock(const std::string& _name) {
	throw eaudiofx::exeption::StdExeption("NOT IMPLEMENTED");
}

void eaudiofx::BlockMeta::replaceFilter(const std::string& _nameUnLink, const std::string& _nameLink) {
	throw eaudiofx::exeption::StdExeption("NOT IMPLEMENTED");
}

void eaudiofx::BlockMeta::linkBlock(const std::string& _generatorBlockName,
                                    const std::string& _generatorIoName,
                                    const std::string& _receiverBlockName,
                                    const std::string& _receiverIoName) {
	
}

void eaudiofx::BlockMeta::openFile(const std::string& _fileName) {
	throw eaudiofx::exeption::StdExeption("NOT IMPLEMENTED");
}

void eaudiofx::BlockMeta::openStream(const std::string& _stream) {
	throw eaudiofx::exeption::StdExeption("NOT IMPLEMENTED");
}

