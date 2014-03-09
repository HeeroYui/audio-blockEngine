/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/base/ReceiverRtAudio.h>
#include <eaudiofx/core/BufferAudioRaw.h>
#include <eaudiofx/debug.h>
#include <rtaudio/RtAudio.h>

int eaudiofx::ReceiverRtAudio::rtAudioCallBack(void *_outputBuffer,
                                               void *_inputBuffer,
                                               unsigned int _nBufferFrames,
                                               double _streamTime,
                                               RtAudioStreamStatus _status,
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
                                            RtAudioStreamStatus _status) {
	// Request block input:
	int32_t ret = eaudiofx::Block::pull(_streamTime, _nBufferFrames, (float)_nBufferFrames/48000.0f);
	if (ret != eaudiofx::ERR_NONE) {
		EAUDIOFX_ERROR("wan not get data ...");
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
		_outputBuffer[iii] = data[iii]*0.05f;
	}
	/*
	FILE* plopppp = fopen("plopout.raw", "a");
	fwrite(_outputBuffer, sizeof(float), _nBufferFrames, plopppp);
	fflush(plopppp);
	fclose(plopppp);
	*/
	return 0;
}



eaudiofx::ReceiverRtAudio::ReceiverRtAudio(void) {
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


int32_t eaudiofx::ReceiverRtAudio::init(void) {
	EAUDIOFX_DEBUG("Create RTAudio generator ...");
	if ( m_dac.getDeviceCount() < 1 ) {
		EAUDIOFX_ERROR("No audio devices found!");
		exit( 0 );
	}
	EAUDIOFX_DEBUG("nb devices :" << m_dac.getDeviceCount() << " default device ID : " << m_dac.getDefaultOutputDevice());
	RtAudio::StreamParameters parameters;
	m_parameters.deviceId = m_dac.getDefaultOutputDevice();
	m_parameters.nChannels = 2;
	m_parameters.firstChannel = 0;
	unsigned int bufferFrames = 256;
	try {
		EAUDIOFX_DEBUG("OPEN Stream ...");
		m_dac.openStream(&m_parameters, NULL, RTAUDIO_FLOAT32, 48000, &bufferFrames, &rtAudioCallBack, (void *)this);
		m_dac.startStream();
	}catch ( RtError& e ) {
		e.printMessage();
		exit( 0 );
	}
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRtAudio::unInit(void) {
	try {
		EAUDIOFX_DEBUG("STOP Stream ...");
		// Stop the stream
		m_dac.stopStream();
	} catch (RtError& e) {
		e.printMessage();
		return eaudiofx::ERR_NONE;
	}
	if ( m_dac.isStreamOpen() ) {
		m_dac.closeStream();
	}
	return eaudiofx::ERR_NONE;
};


