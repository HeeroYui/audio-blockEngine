/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BUFFER_STREAM_H__
#define __EAUDIOFX_BUFFER_STREAM_H__

#include <eaudiofx/core/Buffer.h>

namespace eaudiofx {
	class BufferStream : public eaudiofx::Buffer {
		public:
			BufferStream(eaudiofx::Block& _parent);
			~BufferStream(void);
		protected:
			void*  m_data; //!< buffer data
			size_t m_allocated; //!< number of byte allocated
		protected:
			size_t m_size; //!< number of byte provided in this buffer ... (write by the upstream (can be 0))
		protected:
			size_t m_sizeRequested; //!< in pull mode, number of byte requested by the next Filter
	};
};

#endif


