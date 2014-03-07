/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_ENCODER_H__
#define __EAUDIOFX_BLOCK_ENCODER_H__

#include <eaudiofx/core/Block.h>

namespace eaudiofx {
	class BlockEncoder : public eaudiofx::Block {
		public:
			BlockEncoder(void);
			virtual ~BlockEncoder(void) {};
	};
	
};

#endif


