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
	enum audioFormat {
		audioFormatInt8,
		audioFormatInt16,
		audioFormatInt24,
		audioFormatInt32,
		audioFormatIntFloat,
		audioFormatIntDouble,
		audioFormatInt16OverInt32
	};
	enum audioChannel {
		audioChannelFrontLeft, //!< channel Front Left
		audioChannelFrontCenter, //!< channel Front Center
		audioChannelFrontRight, //!< channel Front Right
		audioChannelRearLeft, //!< channel rear Left
		audioChannelRearCenter, //!< channel rear Center
		audioChannelRearRight, //!< channel rear Right
		audioChannelSurroundLeft, //!< channel surround Left
		audioChannelSurroundRight, //!< channel surround Right
		audioChannelSubWoofer, //!< channel Sub-woofer
		audioChannelLFE //!< channel Low frequency
	};
	class BufferAudio : public eaudiofx::Buffer {
		public:
			BufferAudio(eaudiofx::Block& _parent,
			            int32_t _frequency=48000,
			            const std::vector<enum audioChannel>& _map={audioChannelFrontLeft,audioChannelFrontRight},
			            enum audioFormat _format=audioFormatInt16);
			BufferAudio(eaudiofx::Block& _parent,
			            const std::string& _description);
			virtual ~BufferAudio();
		protected:
			int32_t m_frequency;
			std::vector<enum audioChannel> m_channelMap;
			enum audioFormat m_format;
		protected:
			std::vector<int8_t> m_data; //!< pointer on the data.
			int8_t m_sampleSize; //!< Size of one sample
			int8_t m_chunkSize; //!< Size of one chunk Size
		public:
			/**
			 * @brief Get the buffer casted in float*
			 * @return Pointer on the buffer with correct cast.
			 */
			template<typename T> T* getData() {
				return static_cast<T*>(&m_data[0]);
			}
			/**
			 * @breif Clean all sample in the buffer
			 */
			void clear();
			/**
			 * @brief Resize the buffer at a new size.
			 * @param[in] _nbChunks Number of chunk requested.
			 */
			void resize(size_t _nbChunks);
			/**
			 * @brief Get number of chunk in the buffer.
			 * @return Number of chunk in the buffer.
			 */
			size_t size();
	};
};

#endif


