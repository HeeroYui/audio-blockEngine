/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once
#include <eaudiofx/core/audio.hpp>
#include <eaudiofx/core/Buffer.hpp>
#include <eaudiofx/core/Block.hpp>
#include <eaudiofx/core/BlockMeta.hpp>
#include <eaudiofx/Thread.hpp>
#include <vector>

namespace eaudiofx {
	class Processing : public eaudiofx::BlockMeta, eaudiofx::Thread {
		protected:
			Processing();
			void init() {
				eaudiofx::BlockMeta::init();
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
};



