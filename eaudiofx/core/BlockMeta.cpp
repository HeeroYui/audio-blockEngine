/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <eaudiofx/debug.hpp>
#include <eaudiofx/core/BlockMeta.hpp>


eaudiofx::BlockMeta::BlockMeta() {
	addObjectType("eaudiofx::BlockMeta");
}

eaudiofx::BlockMeta::~BlockMeta() {
	// TODO : Unlink all ...
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		ememory::SharedPtr<eaudiofx::Block> tmp = it;
		it.reset();
	}
	m_list.clear();
}

ememory::SharedPtr<eaudiofx::Block> eaudiofx::BlockMeta::getBlock(const std::string& _name) {
	if (_name.size() == 0) {
		return nullptr;
	}
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		if (it->propertyName.get() == _name) {
			return it;
		}
	}
	return nullptr;
}

int32_t eaudiofx::BlockMeta::addBlock(ememory::SharedPtr<eaudiofx::Block> _block) {
	if (_block == nullptr) {
		EAUDIOFX_ERROR("[" << getId() << "] Add nullptr block");
		return eaudiofx::ERR_INPUT_NULL;
	}
	if (_block->propertyName.get().size() > 0 ) {
		// Check if name exist :
		for (auto &it : m_list) {
			if (it == nullptr) {
				continue;
			}
			if (it->propertyName.get() == _block->propertyName.get()) {
				EAUDIOFX_ERROR("[" << getId() << "] Add block name '" << _block->propertyName.get() << "' already exist");
				return eaudiofx::ERR_ALREADY_EXIST;
			}
		}
	}
	m_list.push_back(_block);
	_block->setParent(sharedFromThis());
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
	ememory::SharedPtr<eaudiofx::Block> receive = getBlock(_receiverBlockName);
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
	EAUDIOFX_INFO("[" << getId() << "]Init Meta block : '" << propertyName << "'");
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
		EAUDIOFX_WARNING("Pb when init the Meta-block '" << propertyName << "' ");
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
		EAUDIOFX_WARNING("Pb when un-init the Meta-block '" << propertyName << "' ");
	}
	return ret;
};


int32_t eaudiofx::BlockMeta::algoStart() {
	EAUDIOFX_INFO("[" << getId() << "] Start Meta block : '" << propertyName << "'");
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
		EAUDIOFX_WARNING("Pb when start the Meta-block '" << propertyName << "' ");
	}
	return ret;
};

int32_t eaudiofx::BlockMeta::algoStop() {
	EAUDIOFX_INFO("[" << getId() << "] Stop Meta block : '" << propertyName << "'");
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
		EAUDIOFX_WARNING("Pb when stop the Meta-block '" << propertyName << "' ");
	}
	return ret;
};


ememory::SharedPtr<eaudiofx::Block> eaudiofx::BlockMeta::getBlockNamed(const std::string& _name) {
	ememory::SharedPtr<eaudiofx::Block> out;
	EAUDIOFX_DEBUG("[" << propertyName << "] try get Block : " << _name);
	// Special case for proxy flow ...
	if (    _name == ""
	     || _name == propertyName.get()) {
		EAUDIOFX_DEBUG("   ==> find Him");
		return ememory::staticPointerCast<eaudiofx::Block>(sharedFromThis());
	}
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		EAUDIOFX_DEBUG("   check : " << it->propertyName.get());
		if (it->propertyName.get() == _name) {
			out = it;
			EAUDIOFX_DEBUG("        ==> find this one");
			break;
		}
	}
	return out;
}

void eaudiofx::BlockMeta::flowLinkInput() {
	EAUDIOFX_INFO("[" << getId() << "] Meta block Link: '" << propertyName << "'");
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


void eaudiofx::BlockMeta::flowCheckAllCompatibility() {
	EAUDIOFX_INFO("[" << getId() << "] Meta block check compatibilities: '" << propertyName << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		it->flowCheckAllCompatibility();
	}
	// Call upper class
	eaudiofx::Block::flowCheckAllCompatibility();
}

void eaudiofx::BlockMeta::flowAllocateOutput() {
	EAUDIOFX_INFO("[" << getId() << "] Meta block allocate output: '" << propertyName << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		it->flowAllocateOutput();
	}
	// Call upper class
	eaudiofx::Block::flowAllocateOutput();
}

void eaudiofx::BlockMeta::flowGetInput() {
	EAUDIOFX_INFO("[" << getId() << "] Meta block get input ... : '" << propertyName << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == nullptr) {
			continue;
		}
		it->flowGetInput();
	}
	// Call upper class
	eaudiofx::Block::flowGetInput();
}
