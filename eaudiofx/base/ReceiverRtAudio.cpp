/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/base/ReceiverRtAudio.h>
#include <eaudiofx/core/BufferAudio.h>
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
int32_t eaudiofx::ReceiverRtAudio::needData(void* _outputBuffer,
                                            size_t _nBufferFrames,
                                            double _streamTime,
                                            airtaudio::streamStatus _status) {
	EAUDIOFX_INFO("NEED DATA : " << _nBufferFrames);
	if (m_processStarted == false) {
		for (int32_t iii=0; iii<_nBufferFrames*2; ++iii) {
			((int8_t*)_outputBuffer)[iii] = 0;
		}
		return 0;
	}
	int32_t nbData = std::min(m_buffer.size()/2, _nBufferFrames*2);
	for (int32_t iii=0; iii<nbData*2; ++iii) {
		((int8_t*)_outputBuffer)[iii] = m_buffer[iii];
		//EAUDIOFX_ERROR("write : " << data[iii]);
	}
	return 0;
}

int32_t eaudiofx::ReceiverRtAudio::algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
	EAUDIOFX_INFO("Process: " << _currentTime << " chunkTime=" << _processTimeSlot);
	return eaudiofx::ERR_NONE;
}


void eaudiofx::ReceiverRtAudio::init() {
	eaudiofx::Block::init();
	
}

eaudiofx::ReceiverRtAudio::ReceiverRtAudio() :
  m_processStarted(false) {
	/*
	// set output :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "in",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioInput,
	      "{ type:'audio', compression:'raw', frequency:48000, channel:2, format:'float' }",
	      NULL
	    ) ) );
	*/
};


int32_t eaudiofx::ReceiverRtAudio::algoInit() {
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
	//m_dac.openStream(&m_parameters, NULL, airtaudio::FLOAT32, 48000, &bufferFrames, &rtAudioCallBack, (void *)this);
	m_dac.openStream(&m_parameters, NULL, airtaudio::SINT16, 48000, &bufferFrames, &rtAudioCallBack, (void *)this);
	// TODO : Check return error
	m_dac.startStream();
	
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRtAudio::algoUnInit() {
	EAUDIOFX_DEBUG("un-init Stream ...");
	// Stop the stream
	m_dac.stopStream();
	// TODO : Check return error
	if ( m_dac.isStreamOpen() ) {
		m_dac.closeStream();
	}
	
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRtAudio::algoStart() {
	EAUDIOFX_DEBUG("Start stream ...");
	m_processStarted = true;
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRtAudio::algoStop() {
	EAUDIOFX_DEBUG("Stop Stream ...");
	m_processStarted = false;
	return eaudiofx::ERR_NONE;
};

