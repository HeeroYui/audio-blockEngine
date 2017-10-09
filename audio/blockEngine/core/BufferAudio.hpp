/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <audio/blockEngine/core/Buffer.hpp>
namespace audio {
	namespace blockEngine {
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
		class BufferAudio : public audio::blockEngine::Buffer {
			public:
				BufferAudio(audio::blockEngine::Block& _parent,
				            int32_t _frequency=48000,
				            const etk::Vector<enum audioChannel>& _map={audioChannelFrontLeft,audioChannelFrontRight},
				            enum audioFormat _format=audioFormatInt16);
				BufferAudio(audio::blockEngine::Block& _parent,
				            const etk::String& _description);
				virtual ~BufferAudio();
			protected:
				int32_t m_frequency;
				etk::Vector<enum audioChannel> m_channelMap;
				enum audioFormat m_format;
			protected:
				etk::Vector<int8_t> m_data; //!< pointer on the data.
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
	}
}


