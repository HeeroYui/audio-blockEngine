/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <audio/blockEngine/core/BlockGenerator.hpp>

namespace audio {
	namespace blockEngine {
		class GeneratorRiver : public audio::blockEngine::BlockGenerator {
			public:
				GeneratorRiver();
				virtual ~GeneratorRiver() {};
			public:
				int32_t pull(double _currentTime, int32_t _request, float _timeout);
		};
	}
}



