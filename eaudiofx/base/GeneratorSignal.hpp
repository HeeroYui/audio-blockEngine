/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <eaudiofx/core/Block.hpp>
#include <eaudiofx/core/BufferAudio.hpp>

namespace eaudiofx {
	class GeneratorSignal : public eaudiofx::Block {
		protected:
			float m_phase;
		protected:
			GeneratorSignal();
			void init();
		public:
			DECLARE_FACTORY(GeneratorSignal);
			virtual ~GeneratorSignal() {};
		public:
			int32_t algoProcess(int64_t _currentTime, int64_t _processTimeSlot);
		protected:
			eaudiofx::flow::Output<eaudiofx::BufferAudio> m_output;
	};
};


