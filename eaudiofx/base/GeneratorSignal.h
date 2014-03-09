/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_GENERATOR_SIGNAL_H__
#define __EAUDIOFX_GENERATOR_SIGNAL_H__

#include <eaudiofx/core/BlockGenerator.h>

namespace eaudiofx {
	class GeneratorSignal : public eaudiofx::BlockGenerator {
		protected:
			float m_phase;
		public:
			GeneratorSignal(void);
			virtual ~GeneratorSignal(void) {};
		public:
			int32_t pull(double _currentTime, int32_t _request, float _timeout);
	};
};

#endif


