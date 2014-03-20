/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/core/BufferStream.h>

eaudiofx::BufferStream::BufferStream(eaudiofx::Block& _parent) :
  eaudiofx::Buffer(_parent),
  m_data(NULL),
  m_allocated(0),
  m_size(0) {
	
}
eaudiofx::BufferStream::~BufferStream(void) {
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
		m_allocated = 0;
	}
}

void eaudiofx::BufferStream::resize(size_t _newSize) {
	if (m_allocated >= _newSize) {
		// nothing to do, enought data ...
		return;
	}
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
		m_allocated = 0;
	}
	EAUDIOFX_ERROR("Request allocate of " << _newSize << " bytes");
	m_data = new uint8_t[_newSize*2];
	if (m_data == NULL) {
		EAUDIOFX_ERROR("Can not allocate Buffer Audio");
	} else {
		m_allocated = _newSize;
	}
}

void eaudiofx::BufferStream::setProperty(int32_t _dataSize) {
	if (_dataSize<=0) {
		return;
	}
	resize(_dataSize);
}