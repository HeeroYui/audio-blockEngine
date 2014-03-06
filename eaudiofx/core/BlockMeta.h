/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_META_H__
#define __EAUDIOFX_BLOCK_META_H__

#include <eaudiofx/core/Block.h>
#include <vector>

namespace eaudiofx {
	class BlockMeta : public eaudiofx::Block {
		public:
			BlockMeta(void);
			~BlockMeta(void);
		private:
			std::vector<eaudiofx::Block*> m_list; //!< list of all block to process.
			
	};
};

#endif


