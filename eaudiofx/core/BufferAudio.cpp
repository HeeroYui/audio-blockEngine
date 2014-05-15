/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/core/BufferAudio.h>
#include <eaudiofx/debug.h>

eaudiofx::BufferAudio::BufferAudio(eaudiofx::Block& _parent) :
  eaudiofx::Buffer(_parent),
  m_frequency(0),
  m_nbChannel(0),
  m_data(NULL),
  m_allocated(0) {
	memset(m_channelType, 0, sizeof(m_channelType));
}

eaudiofx::BufferAudio::BufferAudio(eaudiofx::Block& _parent, int32_t _frequency, int32_t _nbChannel) :
  eaudiofx::Buffer(_parent),
  m_frequency(_frequency),
  m_nbChannel(_nbChannel),
  m_data(NULL),
  m_allocated(0) {
	memset(m_channelType, 0, sizeof(m_channelType));
}

eaudiofx::BufferAudio::~BufferAudio() {
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
		m_allocated = 0;
	}
}

void eaudiofx::BufferAudio::resize(size_t _newSize) {
	if (m_allocated >= _newSize) {
		// nothing to do, enought data ...
		return;
	}
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
		m_allocated = 0;
	}
	EAUDIOFX_ERROR("Request allocate of " << _newSize << " samples");
	m_data = new float[_newSize];
	if (m_data == NULL) {
		EAUDIOFX_ERROR("Can not allocate Buffer Audio");
	} else {
		m_allocated = _newSize;
	}
}