/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_RECEIVER_RTAUDIO_H__
#define __EAUDIOFX_RECEIVER_RTAUDIO_H__

#include <eaudiofx/core/BlockReceiver.h>
#include <rtaudio/RtAudio.h>

namespace eaudiofx {
	class ReceiverRtAudio : public eaudiofx::BlockReceiver {
		private:
			static int rtAudioCallBack(void *_outputBuffer,
			                           void *_inputBuffer,
			                           unsigned int _nBufferFrames,
			                           double _streamTime,
			                           RtAudioStreamStatus _status,
			                           void* _userData);
			// class callback
			int32_t needData(float* _outputBuffer,
			                 size_t _nBufferFrames,
			                 double _streamTime,
			                 RtAudioStreamStatus _status);
		public:
			ReceiverRtAudio(void);
			virtual ~ReceiverRtAudio(void) {};
		public: // herieted function :
			virtual int32_t Init(void);
			virtual int32_t UnInit(void);
		private:
			RtAudio m_dac;
			RtAudio::StreamParameters m_parameters;
	};
};

#endif


