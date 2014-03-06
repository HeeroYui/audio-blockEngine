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
			BufferAudio(void);
			~BufferAudio(void);
		protected:
			int32_t m_frequency;
			int32_t m_nbChannel;
			enum channelPosition m_channelType[MAX_NUMBER_OF_SIMULTANEOUS_CHANNEL];
		protected:
			uint8_t* m_data; //!< pointer on the data.
			size_t m_allocated; //!< number of byte allocated
		protected:
			/**
			 * @brief Reallocate the Buffer data.
			 */
			virtual void resize(size_t _newSizeByte);
	};
};

#endif


