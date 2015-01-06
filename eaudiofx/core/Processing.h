/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_PROCESSING_H__
#define __EAUDIOFX_PROCESSING_H__

#include <eaudiofx/core/audio.h>
#include <eaudiofx/core/Buffer.h>
#include <eaudiofx/core/Block.h>
#include <eaudiofx/core/BlockMeta.h>
#include <vector>

namespace eaudiofx {
	class Processing : public eaudiofx::BlockMeta {
		protected:
			Processing() {};
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
			
	};
};

#endif


