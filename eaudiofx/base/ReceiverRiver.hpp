/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <eaudiofx/core/Block.hpp>
#include <audio/river/Interface.hpp>
#include <audio/river/Manager.hpp>
#include <eaudiofx/core/BufferAudio.hpp>

namespace eaudiofx {
	class ReceiverRiver : public eaudiofx::Block {
		private:
			void onDataNeeded(void* _data,
			                  const audio::Time& _time,
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
			ememory::SharedPtr<audio::river::Manager> m_manager;
			ememory::SharedPtr<audio::river::Interface> m_interface;
			std::vector<int8_t> m_buffer;
		public:
			int32_t algoProcess(int64_t _currentTime, int64_t _processTimeSlot);
		protected:
			eaudiofx::flow::Input<eaudiofx::BufferAudio> m_input;
	};
};



