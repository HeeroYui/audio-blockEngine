/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once
#include <audio/blockEngine/core/audio.hpp>
#include <audio/blockEngine/core/Buffer.hpp>
#include <audio/blockEngine/core/Block.hpp>
#include <audio/blockEngine/core/BlockMeta.hpp>
#include <audio/blockEngine/Thread.hpp>
#include <vector>

namespace audio {
	namespace blockEngine {
		class Processing : public audio::blockEngine::BlockMeta, audio::blockEngine::Thread {
			protected:
				Processing();
				void init() {
					audio::blockEngine::BlockMeta::init();
				};
			public:
				DECLARE_FACTORY(Processing);
				virtual ~Processing() {};
			public:
				int32_t process();
				int32_t start();
				int32_t stop();
				int32_t waitEndOfProcess();
				
				// Thread interface :
				virtual bool stateStart();
				virtual bool stateRun();
				virtual bool stateStop();
		};
	}
}



