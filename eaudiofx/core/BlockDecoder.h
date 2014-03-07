/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_DECODER_H__
#define __EAUDIOFX_BLOCK_DECODER_H__

#include <eaudiofx/core/Block.h>

namespace eaudiofx {
	class BlockDecoder : public eaudiofx::Block {
		public:
			BlockDecoder(void);
			virtual ~BlockDecoder(void) {};
	};
};

#endif


