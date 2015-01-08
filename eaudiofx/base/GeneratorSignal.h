/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_GENERATOR_SIGNAL_H__
#define __EAUDIOFX_GENERATOR_SIGNAL_H__

#include <eaudiofx/core/Block.h>
#include <eaudiofx/core/BufferAudio.h>

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

#endif


