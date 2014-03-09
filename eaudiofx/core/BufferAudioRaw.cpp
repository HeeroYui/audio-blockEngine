/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/core/BufferAudioRaw.h>


eaudiofx::BufferAudioRaw::BufferAudioRaw(eaudiofx::Block& _parent) :
  eaudiofx::BufferAudio(_parent),
  m_allocatedSample(0) {
	
}

eaudiofx::BufferAudioRaw::BufferAudioRaw(eaudiofx::Block& _parent, int32_t _frequency, int32_t _nbChannel, int32_t _nbSample) :
  eaudiofx::BufferAudio(_parent, _frequency, _nbChannel),
  m_allocatedSample(_nbSample) {
	if (_nbSample < 0) {
		m_allocatedSample = 512;
	}
	EAUDIOFX_INFO("Resize the buffer : " << m_frequency << "Hz, " << m_nbChannel << " channel(s), " << m_allocatedSample << " sample(s)");
	resize(m_nbChannel*m_allocatedSample);
}


void eaudiofx::BufferAudioRaw::setProperty(int32_t _frequency, int32_t _nbChannel, int32_t _nbSample) {
	bool increaseSize = false;
	if (_nbSample > m_allocatedSample) {
		m_allocatedSample = _nbSample;
		increaseSize = true;
	}
	if (_nbChannel > m_nbChannel) {
		increaseSize = true;
	}
	m_nbChannel = _nbChannel;
	m_frequency = _frequency;
	if (increaseSize == true) {
		EAUDIOFX_INFO("Resize the buffer : " << m_frequency << "Hz, " << m_nbChannel << " channel(s), " << m_allocatedSample << " sample(s)");
		resize(m_nbChannel*m_allocatedSample);
	}
}