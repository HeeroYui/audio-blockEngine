/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BUFFER_H__
#define __EAUDIOFX_BUFFER_H__

#include <eaudiofx/core/audio.h>
#include <eaudiofx/core/Block.h>

namespace eaudiofx {
	class Block;
	class Buffer : public std::enable_shared_from_this<Buffer> {
		public:
			Buffer(eaudiofx::Block& _parent);
			virtual ~Buffer() {};
		protected:
			eaudiofx::Block& m_parent; //!< parrent Block of this Buffer
		protected:
			int64_t m_timestamp; //!< current buffer time
			int64_t m_timeSize; //!< current buffer data time size
	};
};

#endif


