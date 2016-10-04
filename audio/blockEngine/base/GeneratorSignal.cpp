/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/base/GeneratorSignal.hpp>
#include <audio/blockEngine/core/BufferAudio.hpp>
#include <cmath>

void audio::blockEngine::GeneratorSignal::init() {
	audio::blockEngine::Block::init();
}

audio::blockEngine::GeneratorSignal::GeneratorSignal() :
  m_phase(0),
  m_output(*this, "out", "Output sinus generated", "{ type:'audio', freq:48000, format:['int16','int32'], channels:2}") {
	addObjectType("audio::blockEngine::GeneratorSignal");
}


int32_t audio::blockEngine::GeneratorSignal::algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
	ABE_INFO("Process: " << _currentTime << " chunkTime=" << _processTimeSlot);
	return audio::blockEngine::ERR_NONE;
}
#if 0
int32_t audio::blockEngine::GeneratorSignal::pull(double _currentTime, int32_t _request, float _timeout) {
	auto it = m_io.find("out");
	if (it == m_io.end()) {
		ABE_WARNING("request to pull data with no output !!!");
		return audio::blockEngine::ERR_FAIL;
	}
	audio::blockEngine::BufferAudioRaw* buffer = dynamic_cast<audio::blockEngine::BufferAudioRaw*>(it->second.m_buffer);
	//ABE_ERROR("Generate data, request : " << _request << " at time : " << _currentTime);
	if (buffer == nullptr) {
		// !! impossible case => a buffer can not be removed ...
		ABE_ERROR("Buffer has been removed... OR change type ...");
		return audio::blockEngine::ERR_FAIL;
	}
	//request outpuffer needed size :
	buffer->setProperty(48000, 2, _request);
	float* data = buffer->getData();
	for (int32_t iii=0; iii<_request; ++iii) {
		for (int32_t jjj=0; jjj<2; ++jjj) {
			*data++ = cos(m_phase)*0.5f;
		}
		m_phase += 0.1;
		if (m_phase > 4.0*M_PI) {
			m_phase -= 4.0*M_PI;
		}
	}
	/*
	FILE* plopppp = fopen("plop.raw", "a");
	fwrite(buffer->getData(), sizeof(float), _request*2, plopppp);
	fflush(plopppp);
	fclose(plopppp);
	*/
	return audio::blockEngine::ERR_NONE;
}
#endif
