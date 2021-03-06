/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/core/BlockMeta.hpp>


audio::blockEngine::BlockMeta::BlockMeta() {
	addObjectType("audio::blockEngine::BlockMeta");
}

audio::blockEngine::BlockMeta::~BlockMeta() {
	// TODO : Unlink all ...
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		ememory::SharedPtr<audio::blockEngine::Block> tmp = it;
		it.reset();
	}
	m_list.clear();
}

ememory::SharedPtr<audio::blockEngine::Block> audio::blockEngine::BlockMeta::getBlock(const etk::String& _name) {
	if (_name.size() == 0) {
		return null;
	}
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		if (it->propertyName.get() == _name) {
			return it;
		}
	}
	return null;
}

int32_t audio::blockEngine::BlockMeta::addBlock(ememory::SharedPtr<audio::blockEngine::Block> _block) {
	if (_block == null) {
		ABE_ERROR("[" << getId() << "] Add null block");
		return audio::blockEngine::ERR_INPUT_NULL;
	}
	if (_block->propertyName.get().size() > 0 ) {
		// Check if name exist :
		for (auto &it : m_list) {
			if (it == null) {
				continue;
			}
			if (it->propertyName.get() == _block->propertyName.get()) {
				ABE_ERROR("[" << getId() << "] Add block name '" << _block->propertyName.get() << "' already exist");
				return audio::blockEngine::ERR_ALREADY_EXIST;
			}
		}
	}
	m_list.pushBack(_block);
	_block->setParent(sharedFromThis());
	return audio::blockEngine::ERR_NONE;
}

int32_t audio::blockEngine::BlockMeta::addBlock(const etk::String& _blockType, const etk::String& _name) {
	ABE_ERROR("NOT IMPLEMENTED");
	return audio::blockEngine::ERR_NOT_IMPLEMENTED;
}

int32_t audio::blockEngine::BlockMeta::removeBlock(const etk::String& _name) {
	ABE_ERROR("NOT IMPLEMENTED");
	return audio::blockEngine::ERR_NOT_IMPLEMENTED;
}


int32_t audio::blockEngine::BlockMeta::linkBlock(const etk::String& _generatorBlockName,
                                       const etk::String& _generatorIoName,
                                       const etk::String& _receiverBlockName,
                                       const etk::String& _receiverIoName) {
	// TODO : proxy IOs
	ememory::SharedPtr<audio::blockEngine::Block> receive = getBlock(_receiverBlockName);
	if (receive == null) {
		ABE_ERROR("Can not find destination block : '" << _receiverBlockName << "'");
		return audio::blockEngine::ERR_FAIL;
	}
	receive->flowSetLinkWith(_receiverIoName, _generatorBlockName, _generatorIoName);
	return audio::blockEngine::ERR_NONE;
}

int32_t audio::blockEngine::BlockMeta::openFile(const etk::String& _fileName) {
	ABE_ERROR("NOT IMPLEMENTED");
	return audio::blockEngine::ERR_NOT_IMPLEMENTED;
}

int32_t audio::blockEngine::BlockMeta::openStream(const etk::String& _stream) {
	ABE_ERROR("NOT IMPLEMENTED");
	return audio::blockEngine::ERR_NOT_IMPLEMENTED;
}


int32_t audio::blockEngine::BlockMeta::algoInit() {
	ABE_INFO("[" << getId() << "]Init Meta block : '" << propertyName << "'");
	int32_t ret = audio::blockEngine::ERR_NONE;
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		if (it->algoInit() != audio::blockEngine::ERR_NONE) {
			ret = audio::blockEngine::ERR_FAIL;
		}
	}
	if (ret != audio::blockEngine::ERR_NONE) {
		ABE_WARNING("Pb when init the Meta-block '" << propertyName << "' ");
	}
	return ret;
};

int32_t audio::blockEngine::BlockMeta::algoUnInit() {
	int32_t ret = audio::blockEngine::ERR_NONE;
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		if (it->algoUnInit() != audio::blockEngine::ERR_NONE) {
			ret = audio::blockEngine::ERR_FAIL;
		}
	}
	if (ret != audio::blockEngine::ERR_NONE) {
		ABE_WARNING("Pb when un-init the Meta-block '" << propertyName << "' ");
	}
	return ret;
};


int32_t audio::blockEngine::BlockMeta::algoStart() {
	ABE_INFO("[" << getId() << "] Start Meta block : '" << propertyName << "'");
	int32_t ret = audio::blockEngine::ERR_NONE;
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		if (it->algoStart() != audio::blockEngine::ERR_NONE) {
			ret = audio::blockEngine::ERR_FAIL;
		}
	}
	if (ret != audio::blockEngine::ERR_NONE) {
		ABE_WARNING("Pb when start the Meta-block '" << propertyName << "' ");
	}
	return ret;
};

int32_t audio::blockEngine::BlockMeta::algoStop() {
	ABE_INFO("[" << getId() << "] Stop Meta block : '" << propertyName << "'");
	int32_t ret = audio::blockEngine::ERR_NONE;
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		if (it->algoStop() != audio::blockEngine::ERR_NONE) {
			ret = audio::blockEngine::ERR_FAIL;
		}
	}
	if (ret != audio::blockEngine::ERR_NONE) {
		ABE_WARNING("Pb when stop the Meta-block '" << propertyName << "' ");
	}
	return ret;
};


ememory::SharedPtr<audio::blockEngine::Block> audio::blockEngine::BlockMeta::getBlockNamed(const etk::String& _name) {
	ememory::SharedPtr<audio::blockEngine::Block> out;
	ABE_DEBUG("[" << propertyName << "] try get Block : " << _name);
	// Special case for proxy flow ...
	if (    _name == ""
	     || _name == propertyName.get()) {
		ABE_DEBUG("   ==> find Him");
		return ememory::staticPointerCast<audio::blockEngine::Block>(sharedFromThis());
	}
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		ABE_DEBUG("   check : " << it->propertyName.get());
		if (it->propertyName.get() == _name) {
			out = it;
			ABE_DEBUG("        ==> find this one");
			break;
		}
	}
	return out;
}

void audio::blockEngine::BlockMeta::flowLinkInput() {
	ABE_INFO("[" << getId() << "] Meta block Link: '" << propertyName << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		it->flowLinkInput();
	}
	// Call upper class
	audio::blockEngine::Block::flowLinkInput();
}


void audio::blockEngine::BlockMeta::flowCheckAllCompatibility() {
	ABE_INFO("[" << getId() << "] Meta block check compatibilities: '" << propertyName << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		it->flowCheckAllCompatibility();
	}
	// Call upper class
	audio::blockEngine::Block::flowCheckAllCompatibility();
}

void audio::blockEngine::BlockMeta::flowAllocateOutput() {
	ABE_INFO("[" << getId() << "] Meta block allocate output: '" << propertyName << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		it->flowAllocateOutput();
	}
	// Call upper class
	audio::blockEngine::Block::flowAllocateOutput();
}

void audio::blockEngine::BlockMeta::flowGetInput() {
	ABE_INFO("[" << getId() << "] Meta block get input ... : '" << propertyName << "'");
	// find in sub elements.
	for (auto &it : m_list) {
		if (it == null) {
			continue;
		}
		it->flowGetInput();
	}
	// Call upper class
	audio::blockEngine::Block::flowGetInput();
}
