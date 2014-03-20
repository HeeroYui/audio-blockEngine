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

eaudiofx::Block* eaudiofx::BlockMeta::getBlock(const std::string& _name) {
	if (_name.size() == 0) {
		return NULL;
	}
	for (auto &it : m_list) {
		if (it == NULL) {
			continue;
		}
		if (it->getName() == _name) {
			return it;
		}
	}
	return NULL;
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
	eaudiofx::Block* itGenerator = getBlock(_generatorBlockName);
	eaudiofx::Block* itReceiver = getBlock(_receiverBlockName);
	if (    itGenerator == NULL
	     || itReceiver == NULL) {
		EAUDIOFX_ERROR("Can not link : '" << _generatorBlockName << "' and '" << _receiverBlockName << "' one element does not exist ...");
		return eaudiofx::ERR_FAIL;
	}
	eaudiofx::Buffer* outputBuffer = NULL;
	if (itGenerator->getBuffer(outputBuffer, _generatorIoName) != eaudiofx::ERR_NONE) {
		EAUDIOFX_ERROR("Can not get buffer : '" << _generatorBlockName << "':'" << _generatorIoName << "'");
		return eaudiofx::ERR_FAIL;
	}
	if (outputBuffer == NULL) {
		EAUDIOFX_ERROR("Get NULL buffer : '" << _generatorBlockName << "':'" << _generatorIoName << "'");
		return eaudiofx::ERR_FAIL;
	}
	if (itReceiver->linkBuffer(outputBuffer, _receiverIoName) != eaudiofx::ERR_NONE) {
		EAUDIOFX_ERROR("Can not Link buffer : '" << _receiverBlockName << "':'" << _receiverIoName << "'");
		return eaudiofx::ERR_FAIL;
	}
	EAUDIOFX_INFO("Link : " << _generatorBlockName << ":" << _generatorIoName << " and " << _receiverBlockName << ":" << _receiverIoName);
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


int32_t eaudiofx::BlockMeta::init(void) {
	EAUDIOFX_INFO("[" << getUID() << "]Init Meta block : '" << getName() << "'");
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == NULL) {
			continue;
		}
		if (it->init() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when init the Meta-block '" << getName() << "' ");
	}
	return ret;
};

int32_t eaudiofx::BlockMeta::unInit(void) {
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == NULL) {
			continue;
		}
		if (it->unInit() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when un-init the Meta-block '" << getName() << "' ");
	}
	return ret;
};


int32_t eaudiofx::BlockMeta::start(void) {
	EAUDIOFX_INFO("[" << getUID() << "] Start Meta block : '" << getName() << "'");
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == NULL) {
			continue;
		}
		if (it->start() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when start the Meta-block '" << getName() << "' ");
	}
	return ret;
};

int32_t eaudiofx::BlockMeta::stop(void) {
	EAUDIOFX_INFO("[" << getUID() << "] Stop Meta block : '" << getName() << "'");
	int32_t ret = eaudiofx::ERR_NONE;
	for (auto &it : m_list) {
		if (it == NULL) {
			continue;
		}
		if (it->stop() != eaudiofx::ERR_NONE) {
			ret = eaudiofx::ERR_FAIL;
		}
	}
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_WARNING("Pb when stop the Meta-block '" << getName() << "' ");
	}
	return ret;
};

