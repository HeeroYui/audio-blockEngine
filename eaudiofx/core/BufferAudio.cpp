/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <eaudiofx/core/BufferAudio.hpp>
#include <eaudiofx/debug.hpp>


eaudiofx::BufferAudio::BufferAudio(eaudiofx::Block& _parent, const std::string& _description) :
  eaudiofx::Buffer(_parent),
  m_frequency(48000),
  m_channelMap({audioChannelFrontLeft,audioChannelFrontRight}),
  m_format(audioFormatInt16),
  m_data(),
  m_sampleSize(2),
  m_chunkSize(4) {
	resize(32);
}

eaudiofx::BufferAudio::BufferAudio(eaudiofx::Block& _parent,
                                   int32_t _frequency,
                                   const std::vector<enum audioChannel>& _map,
                                   enum audioFormat _format) :
  eaudiofx::Buffer(_parent),
  m_frequency(_frequency),
  m_channelMap(_map),
  m_format(_format),
  m_data(),
  m_sampleSize(1),
  m_chunkSize(1) {
	switch(_format) {
		case audioFormatInt8:
			m_sampleSize = 1;
			break;
		case audioFormatInt16:
			m_sampleSize = 2;
			break;
		case audioFormatInt24:
		case audioFormatInt32:
		case audioFormatIntFloat:
		case audioFormatInt16OverInt32:
			m_sampleSize = 4;
			break;
		case audioFormatIntDouble:
			m_sampleSize = 8;
			break;
	}
	m_chunkSize = m_sampleSize*m_channelMap.size();
	resize(32);
}

eaudiofx::BufferAudio::~BufferAudio() {
	
}

void eaudiofx::BufferAudio::clear() {
	for (auto &it : m_data) {
		it = 0;
	}
}

void eaudiofx::BufferAudio::resize(size_t _nbChunks) {
	m_data.resize(m_chunkSize*_nbChunks, 0);
}

size_t eaudiofx::BufferAudio::size() {
	return m_data.size() / m_chunkSize;
}

