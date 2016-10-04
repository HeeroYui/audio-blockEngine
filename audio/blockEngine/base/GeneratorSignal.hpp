/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <audio/blockEngine/core/Block.hpp>
#include <audio/blockEngine/core/BufferAudio.hpp>

namespace audio {
	namespace blockEngine {
		class GeneratorSignal : public audio::blockEngine::Block {
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
				audio::blockEngine::flow::Output<audio::blockEngine::BufferAudio> m_output;
		};
	}
}


