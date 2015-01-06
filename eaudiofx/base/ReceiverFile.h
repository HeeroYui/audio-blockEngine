/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_RECEIVER_FILE_H__
#define __EAUDIOFX_RECEIVER_FILE_H__

#include <eaudiofx/core/BlockReceiver.h>
#include <etk/os/FSNode.h>

namespace eaudiofx {
	class ReceiverFile : public eaudiofx::BlockReceiver {
		public:
			ReceiverFile();
			virtual ~ReceiverFile() {};
		public: // herieted function :
			virtual int32_t init();
			virtual int32_t unInit();
		private:
			etk::FSNode* m_file;
			uint32_t m_channels;
			uint32_t m_frequency;
			uint32_t m_requestSize;
			bool m_processStarted;
		public:
			virtual int32_t start();
			virtual int32_t stop();
	};
};

#endif


