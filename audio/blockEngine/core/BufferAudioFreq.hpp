/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <audio/blockEngine/core/BufferAudio.hpp>

namespace audio {
	namespace blockEngine {
		class BufferAudioFreq : public audio::blockEngine::BufferAudio {
			public:
				BufferAudioFreq(audio::blockEngine::Block& _parent);
				virtual ~BufferAudioFreq() {};
		};
	}
}


