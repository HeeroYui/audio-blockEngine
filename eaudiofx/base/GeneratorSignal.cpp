/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/base/GeneratorSignal.h>
#include <eaudiofx/core/BufferAudio.h>
#include <math.h>


#undef __class__
#define __class__ "GeneratorSignal"

void eaudiofx::GeneratorSignal::init() {
	eaudiofx::Block::init();
}

eaudiofx::GeneratorSignal::GeneratorSignal() :
  m_phase(0),
  m_output(*this, "out", "Output sinus generated", "{ type:'audio', freq:48000, format:['int16','int32'], channels:2}") {
	addObjectType("eaudiofx::GeneratorSignal");
}


int32_t eaudiofx::GeneratorSignal::algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
	EAUDIOFX_INFO("Process: " << _currentTime << " chunkTime=" << _processTimeSlot);
	return eaudiofx::ERR_NONE;
}
#if 0
int32_t eaudiofx::GeneratorSignal::pull(double _currentTime, int32_t _request, float _timeout) {
	auto it = m_io.find("out");
	if (it == m_io.end()) {
		EAUDIOFX_WARNING("request to pull data with no output !!!");
		return eaudiofx::ERR_FAIL;
	}
	eaudiofx::BufferAudioRaw* buffer = dynamic_cast<eaudiofx::BufferAudioRaw*>(it->second.m_buffer);
	//EAUDIOFX_ERROR("Generate data, request : " << _request << " at time : " << _currentTime);
	if (buffer == NULL) {
		// !! impossible case => a buffer can not be removed ...
		EAUDIOFX_ERROR("Buffer has been removed... OR change type ...");
		return eaudiofx::ERR_FAIL;
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
	return eaudiofx::ERR_NONE;
}
#endif
