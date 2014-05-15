/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BUFFER_AUDIO_H__
#define __EAUDIOFX_BUFFER_AUDIO_H__

#include <eaudiofx/core/Buffer.h>

namespace eaudiofx {
	class BufferAudio : public eaudiofx::Buffer {
		public:
			BufferAudio(eaudiofx::Block& _parent);
			BufferAudio(eaudiofx::Block& _parent, int32_t _frequency, int32_t _nbChannel);
			virtual ~BufferAudio();
		protected:
			int32_t m_frequency;
			int32_t m_nbChannel;
			enum channelPosition m_channelType[MAX_NUMBER_OF_SIMULTANEOUS_CHANNEL];
		protected:
			float* m_data; //!< pointer on the data.
			size_t m_allocated; //!< number of sample allocated
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
			float* getData() {
				return m_data;
			}
	};
};

#endif


