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



eaudiofx::Block::Block(void) :
  m_uid(0),
  m_type(),
  m_parent(NULL) {
	static size_t id=0;
	m_uid = id;
	id++;
}

eaudiofx::Block::~Block(void) {
	for (auto &it : m_io) {
		if (it.second.m_buffer == NULL) {
			continue;
		}
		if (it.second.m_internal != true) {
			continue;
		}
		// just remove pointer from reference system.
		eaudiofx::Buffer* tmp = it.second.m_buffer;
		it.second.m_buffer = NULL;
		// Notify all element that a buffer is removed.
		subRemoveBuffer(tmp);
		delete(tmp);
	}
}

void eaudiofx::Block::subRemoveBuffer(const eaudiofx::Buffer* _buffer) {
	if (_buffer == NULL) {
		return;
	}
	if (m_parent == NULL) {
		onRemoveBuffer(_buffer);
	} else {
		m_parent->subRemoveBuffer(_buffer);
	}
}

void eaudiofx::Block::onRemoveBuffer(const eaudiofx::Buffer* _buffer) {
	// For every buffer, remove internal reference...
	for (auto &it : m_io) {
		if (it.second.m_buffer == _buffer) {
			it.second.m_buffer = NULL;
		}
	}
}

int32_t eaudiofx::Block::linkBuffer(eaudiofx::Buffer* _buffer, const std::string& _name) {
	for (auto &it : m_io) {
		if (it.first == _name) {
			if (it.second.m_type == ioOutput) {
				EAUDIOFX_ERROR("[" << getUID() << "Can not overwrite output buffer...");
				return eaudiofx::ERR_FORBIDEN;
			}
			it.second.m_buffer = _buffer;
			return eaudiofx::ERR_NONE;
		}
	}
	return eaudiofx::ERR_NO_IO;
}

int32_t eaudiofx::Block::getBuffer(eaudiofx::Buffer*& _buffer, const std::string& _name) {
	for (auto &it : m_io) {
		if (it.first == _name) {
			if (it.second.m_type == ioInput) {
				EAUDIOFX_ERROR("[" << getUID() << "Can not Request Input buffer...");
				return eaudiofx::ERR_FORBIDEN;
			}
			if (it.second.m_type == ioParameter) {
				EAUDIOFX_ERROR("[" << getUID() << "Can not Request Parameter buffer...");
				return eaudiofx::ERR_FORBIDEN;
			}
			_buffer = it.second.m_buffer;
			return eaudiofx::ERR_NONE;
		}
	}
	return eaudiofx::ERR_NO_IO;
}

