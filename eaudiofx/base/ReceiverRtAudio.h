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
#include <airtaudio/Interface.h>

namespace eaudiofx {
	class ReceiverRtAudio : public eaudiofx::BlockReceiver {
		private:
			static int rtAudioCallBack(void *_outputBuffer,
			                           void *_inputBuffer,
			                           unsigned int _nBufferFrames,
			                           double _streamTime,
			                           airtaudio::streamStatus _status,
			                           void* _userData);
			// class callback
			int32_t needData(float* _outputBuffer,
			                 size_t _nBufferFrames,
			                 double _streamTime,
			                 airtaudio::streamStatus _status);
		public:
			ReceiverRtAudio();
			virtual ~ReceiverRtAudio() {};
		public: // herieted function :
			virtual int32_t init();
			virtual int32_t unInit();
		private:
			bool m_processStarted;
		public:
			virtual int32_t start();
			virtual int32_t stop();
		protected:
			airtaudio::Interface m_dac;
			airtaudio::StreamParameters m_parameters;
	};
};

#endif


