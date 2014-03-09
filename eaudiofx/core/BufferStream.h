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
			virtual ~BufferStream(void);
		protected:
			uint8_t* m_data; //!< buffer data
			size_t m_allocated; //!< number of byte allocated
		protected:
			size_t m_size; //!< number of byte provided in this buffer ... (write by the upstream (can be 0))
		public:
			void setAvaillableSize(size_t _availlableSize) {
				m_size = _availlableSize;
			}
			size_t setAvaillableSize(void) {
				return m_size;
			}
		public:
			void setProperty(int32_t _dataSize);
		protected:
			/**
			 * @brief Reallocate the Buffer data.
			 */
			virtual void resize(size_t _newSize);
		public:
			/**
			 * @brief Get the buffer casted in float*
			 * @return Pointer on the buffer with correct cast.
			 */
			uint8_t* getData(void) {
				return m_data;
			}
	};
};

#endif


