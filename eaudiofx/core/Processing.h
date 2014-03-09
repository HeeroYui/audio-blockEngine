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
		public:
			Processing(void) {};
			virtual ~Processing(void) {};
		public:
			int32_t process(void);
			int32_t start(void);
			int32_t stop(void);
			int32_t waitEndOfProcess(void);
			bool isLiveStream(void) {
				return false;
			}
			
	};
};

#endif


