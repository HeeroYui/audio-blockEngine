/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_RECEIVER_RTAUDIO_H__
#define __EAUDIOFX_RECEIVER_RTAUDIO_H__

#include <eaudiofx/core/Block.h>
#include <airtaudio/Interface.h>

namespace eaudiofx {
	class ReceiverRtAudio : public eaudiofx::Block {
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
		protected:
			ReceiverRtAudio();
			void init();
		public:
			DECLARE_FACTORY(ReceiverRtAudio);
			virtual ~ReceiverRtAudio() {};
		public: // herieted function :
			virtual int32_t algoInit();
			virtual int32_t algoUnInit();
		private:
			bool m_processStarted;
		public:
			virtual int32_t algoStart();
			virtual int32_t algoStop();
		protected:
			airtaudio::Interface m_dac;
			airtaudio::StreamParameters m_parameters;
		public:
			int32_t algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
				return eaudiofx::ERR_NONE;
			}
	};
};

#endif


