/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/base/ReceiverRtAudio.h>
#include <eaudiofx/core/BufferAudioRaw.h>
#include <airtaudio/Interface.h>

int eaudiofx::ReceiverRtAudio::rtAudioCallBack(void *_outputBuffer,
                                               void *_inputBuffer,
                                               unsigned int _nBufferFrames,
                                               double _streamTime,
                                               airtaudio::streamStatus _status,
                                               void* _userData) {
	if (_userData == NULL) {
		EAUDIOFX_ERROR("Null class pointer");
		return -1;
	}
	if (_outputBuffer == NULL) {
		EAUDIOFX_ERROR("Null output buffer pointer");
		return -1;
	}
	eaudiofx::ReceiverRtAudio* classPointer = static_cast<eaudiofx::ReceiverRtAudio*>(_userData);
	if (classPointer == NULL) {
		EAUDIOFX_ERROR("Wrong class pointer data");
		return -1;
	}
	
	return classPointer->needData((float*)_outputBuffer, _nBufferFrames, _streamTime, _status);
}

int32_t eaudiofx::ReceiverRtAudio::needData(float* _outputBuffer,
                                            size_t _nBufferFrames,
                                            double _streamTime,
                                            airtaudio::streamStatus _status) {
	if (m_processStarted == false) {
		for (int32_t iii=0; iii<_nBufferFrames*2; ++iii) {
			_outputBuffer[iii] = 0;
		}
		return 0;
	}
	// Request block input:
	int32_t ret = eaudiofx::Block::pull(_streamTime, _nBufferFrames, (float)_nBufferFrames/48000.0f);
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_ERROR("can not get data ...");
		return -1;
	}
	auto it = m_io.find("in");
	if (it == m_io.end()) {
		EAUDIOFX_WARNING("Request an un-existing IO");
		return 0;
	}
	eaudiofx::BufferAudioRaw* buffer = dynamic_cast<eaudiofx::BufferAudioRaw*>(it->second.m_buffer);
	if (buffer == NULL) {
		EAUDIOFX_WARNING("no IO plugged");
		return 0;
	}
	float* data = buffer->getData();
	for (int32_t iii=0; iii<_nBufferFrames*2; ++iii) {
		_outputBuffer[iii] = data[iii]*0.5f;
		//EAUDIOFX_ERROR("write : " << data[iii]);
	}
	/*
	FILE* plopppp = fopen("plopout.raw", "a");
	fwrite(_outputBuffer, sizeof(float), _nBufferFrames, plopppp);
	fflush(plopppp);
	fclose(plopppp);
	*/
	return 0;
}



eaudiofx::ReceiverRtAudio::ReceiverRtAudio() :
  m_processStarted(false) {
	setLive(true);
	// set output :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "in",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioInput,
	      "{ type:'audio', compression:'raw', frequency:48000, channel:2, format:'float' }",
	      NULL
	    ) ) );
	
};


int32_t eaudiofx::ReceiverRtAudio::init() {
	EAUDIOFX_DEBUG("Intanciat AirTAudio Interface ...");
	m_dac.instanciate();
	EAUDIOFX_DEBUG("Create RTAudio receiver ...");
	if ( m_dac.getDeviceCount() < 1 ) {
		EAUDIOFX_ERROR("No audio devices found!");
		return eaudiofx::ERR_FAIL;
	}
	EAUDIOFX_DEBUG("nb devices :" << m_dac.getDeviceCount() << " default device ID : " << m_dac.getDefaultOutputDevice());
	m_parameters.deviceId = m_dac.getDefaultOutputDevice();
	m_parameters.nChannels = 2;
	m_parameters.firstChannel = 0;
	unsigned int bufferFrames = 256;
	EAUDIOFX_DEBUG("init Stream ...");
	// TODO : Check return error
	m_dac.openStream(&m_parameters, NULL, airtaudio::FLOAT32, 48000, &bufferFrames, &rtAudioCallBack, (void *)this);
	// TODO : Check return error
	m_dac.startStream();
	
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRtAudio::unInit() {
	EAUDIOFX_DEBUG("un-init Stream ...");
	// Stop the stream
	m_dac.stopStream();
	// TODO : Check return error
	if ( m_dac.isStreamOpen() ) {
		m_dac.closeStream();
	}
	
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRtAudio::start() {
	EAUDIOFX_DEBUG("Start stream ...");
	m_processStarted = true;
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRtAudio::stop() {
	EAUDIOFX_DEBUG("Stop Stream ...");
	m_processStarted = false;
	return eaudiofx::ERR_NONE;
};

