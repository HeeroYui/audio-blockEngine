/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/core/BufferAudio.h>
#include <eaudiofx/debug.h>

eaudiofx::BufferAudio::BufferAudio(void) :
  m_frequency(0),
  m_nbChannel(0),
  m_data(0),
  m_allocated(0) {
	memset(m_channelType, 0, sizeof(m_channelType));
}

eaudiofx::BufferAudio::~BufferAudio(void) {
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
	}
}

void eaudiofx::BufferAudio::resize(size_t _newSizeByte) {
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
	}
	m_data = new uint8_t[_newSizeByte];
	if (m_data == NULL) {
		EAUDIOFX_ERROR("Can not allocate Buffer Audio");
	}
}