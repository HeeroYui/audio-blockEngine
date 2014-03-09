/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/base/GeneratorSignal.h>
#include <eaudiofx/core/BufferAudioRaw.h>
#include <math.h>


eaudiofx::GeneratorSignal::GeneratorSignal(void) :
  m_phase(0) {
	// set output :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "out",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioOutput,
	      "{ type:'audio', compression:'raw', frequency:48000, channel:2, format:'float' }",
	      new eaudiofx::BufferAudioRaw(*this, 48000, 2)
	    ) ) );
	
}

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