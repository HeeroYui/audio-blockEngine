/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_RECEIVER_RIVER_H__
#define __EAUDIOFX_RECEIVER_RIVER_H__

#include <eaudiofx/core/Block.h>
#include <river/Interface.h>
#include <river/Manager.h>
#include <eaudiofx/core/BufferAudio.h>

namespace eaudiofx {
	class ReceiverRiver : public eaudiofx::Block {
		private:
			void onDataNeeded(void* _data,
			                  const std11::chrono::system_clock::time_point& _time,
			                  size_t _nbChunk,
			                  enum audio::format _format,
			                  uint32_t _frequency,
			                  const std::vector<audio::channel>& _map);
		protected:
			ReceiverRiver();
			void init();
		public:
			DECLARE_FACTORY(ReceiverRiver);
			virtual ~ReceiverRiver() {};
		public: // herieted function :
			virtual int32_t algoInit();
			virtual int32_t algoUnInit();
		private:
			bool m_processStarted;
		public:
			virtual int32_t algoStart();
			virtual int32_t algoStop();
		protected:
			std11::shared_ptr<river::Manager> m_manager;
			std11::shared_ptr<river::Interface> m_interface;
			std::vector<int8_t> m_buffer;
		public:
			int32_t algoProcess(int64_t _currentTime, int64_t _processTimeSlot);
		protected:
			eaudiofx::flow::Input<eaudiofx::BufferAudio> m_input;
	};
};

#endif


