/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/core/BlockMeta.h>

#undef __class__
#define __class__ "BlockMeta"


eaudiofx::BlockMeta::BlockMeta() {
	addObjectType("eaudiofx::BlockMeta");
}

eaudiofx::BlockMeta::~BlockMeta() {
	// TODO : Unlink all ...
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		std::shared_ptr<eaudiofx::Block> tmp = it;
		it.reset();
	}
	m_list.clear();
}

std::shared_ptr<eaudiofx::Block> eaudiofx::BlockMeta::getBlock(const std::string& _name) {
	if (_name.size() == 0) {
		return nullptr;
	}
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		if (it->getName() == _name) {
			return it;
		}
	}
	return nullptr;
}

int32_t eaudiofx::BlockMeta::addBlock(const std::shared_ptr<eaudiofx::Block>& _block) {
	if (_block == nullptr) {
		EAUDIOFX_ERROR("[" << getId() << "] Add nullptr block");
		return eaudiofx::ERR_INPUT_NULL;
	}
	if (_block->getName().size() > 0 ) {
		// Check if name exist :
		for (auto &it : m_list) {
			if (it == nullptr) {
				continue;
			}
			if (it->getName() == _block->getName()) {
				EAUDIOFX_ERROR("[" << getId() << "] Add block name '" << _block->getName() << "' already exist");
				return eaudiofx::ERR_ALREADY_EXIST;
			}
		}
	}
	m_list.push_back(_block);
	_block->setParent(shared_from_this());
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


int32_t eaudiofx::BlockMeta::linkBlock(const std::string& _generatorBlockName,
                                       const std::string& _generatorIoName,
                                       const std::string& _receiverBlockName,
                                       const std::string& _receiverIoName) {
	// TODO : proxy IOs
	std::shared_ptr<eaudiofx::Block> receive = getBlock(_receiverBlockName);
	if (receive == nullptr) {
		EAUDIOFX_ERROR("Can not find destination block : '" << _receiverBlockName << "'");
		return eaudiofx::ERR_FAIL;
	}
	receive->flowSetLinkWith(_receiverIoName, _generatorBlockName, _generatorIoName);
	return eaudiofx::ERR_NONE;
}

int32_t eaudiofx::BlockMeta::openFile(const std::string& _fileName) {
	EAUDIOFX_ERROR("NOT IMPLEMENTED");
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}

int32_t eaudiofx::BlockMeta::openStream(const std::string& _stream) {
	EAUDIOFX_ERROR("NOT IMPLEMENTED");
	return eaudiofx::ERR_NOT_IMPLEMENTED;
}


int32_t eaudiofx::BlockMeta::algoInit() {
	EAUDIOFX_INFO("[" << getId() << "]Init Meta block : '" << getName() << "'");
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		if (it->algoInit() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when init the Meta-block '" << getName() << "' ");
	}
	return ret;
};

int32_t eaudiofx::BlockMeta::algoUnInit() {
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		if (it->algoUnInit() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when un-init the Meta-block '" << getName() << "' ");
	}
	return ret;
};


int32_t eaudiofx::BlockMeta::algoStart() {
	EAUDIOFX_INFO("[" << getId() << "] Start Meta block : '" << getName() << "'");
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		if (it->algoStart() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when start the Meta-block '" << getName() << "' ");
	}
	return ret;
};

int32_t eaudiofx::BlockMeta::algoStop() {
	EAUDIOFX_INFO("[" << getId() << "] Stop Meta block : '" << getName() << "'");
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		if (it->algoStop() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when stop the Meta-block '" << getName() << "' ");
	}
	return ret;
};


std::shared_ptr<eaudiofx::Block> eaudiofx::BlockMeta::getBlockNamed(const std::string& _name) {
	std::shared_ptr<eaudiofx::Block> out;
	EAUDIOFX_DEBUG("[" << m_name << "] try get Block : " << _name);
	// Special case for proxy flow ...
	if (    _name == ""
	     || _name == m_name.get()) {
		EAUDIOFX_DEBUG("   ==> find Him");
		return std::static_pointer_cast<eaudiofx::Block>(shared_from_this());
	}
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		EAUDIOFX_DEBUG("   check : " << it->getName());
		if (it->getName() == _name) {
			out = it;
			EAUDIOFX_DEBUG("        ==> find this one");
			break;
		}
	}
	return out;
}

void eaudiofx::BlockMeta::flowLinkInput() {
	EAUDIOFX_INFO("[" << getId() << "] Meta block Link: '" << getName() << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		it->flowLinkInput();
	}
	// Call upper class
	eaudiofx::Block::flowLinkInput();
}
