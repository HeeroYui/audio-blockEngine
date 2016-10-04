/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <eaudiofx/core/BlockReceiver.hpp>
#include <etk/os/FSNode.hpp>

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


