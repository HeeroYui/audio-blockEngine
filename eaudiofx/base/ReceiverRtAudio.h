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

namespace eaudiofx {
	class ReceiverRtAudio : public eaudiofx::BlockReceiver {
		public:
			ReceiverRtAudio(void) {};
			~ReceiverRtAudio(void) {};
	};
	
};

#endif


