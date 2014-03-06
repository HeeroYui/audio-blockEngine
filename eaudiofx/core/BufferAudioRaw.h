/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BUFFER_AUDIO_RAW_H__
#define __EAUDIOFX_BUFFER_AUDIO_RAW_H__

#include <eaudiofx/core/BufferAudio.h>

namespace eaudiofx {
	class BufferAudioRaw : public eaudiofx::BufferAudio {
		public:
			BufferAudioRaw(void) {};
			~BufferAudioRaw(void) {};
		protected:
			size_t m_allocatedSample; //!< generate with m_allocatedBytes/sizeof(**m_audioFormat**) / m_nbChannel;
		protected:
			size_t m_size; //!< number of sample for each channels provided in this buffer ... (write by the upstream (can be 0))
		protected:
			size_t m_sizeRequested; //!< in pull mode, number of sample for each channels requested by the next Filter
		protected:
			enum audioRawFormat m_audioFormat;
		public:
			/**
			 * @brief Get the buffer casted in void*
			 * @return Pointer on the buffer with correct cast.
			 */
			void* getDataVoid(void) {
				return (void*)m_data;
			}
			/**
			 * @brief Get the buffer casted in int8_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			int8_t* getDataI8(void) {
				return (int8_t*)m_data;
			}
			/**
			 * @brief Get the buffer casted in int16_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			int16_t* getDataI16(void) {
				return (int16_t*)m_data;
			}
			/**
			 * @brief Get the buffer casted in int32_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			int32_t* getDataI32(void) {
				return (int32_t*)m_data;
			}
			/**
			 * @brief Get the buffer casted in int64_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			int64_t* getDataI64(void) {
				return (int64_t*)m_data;
			}
			/**
			 * @brief Get the buffer casted in uint8_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			uint8_t* getDataU8(void) {
				return (uint8_t*)m_data;
			}
			/**
			 * @brief Get the buffer casted in uint16_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			uint16_t* getDataU16(void) {
				return (uint16_t*)m_data;
			}
			/**
			 * @brief Get the buffer casted in uint32_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			uint32_t* getDataU32(void) {
				return (uint32_t*)m_data;
			}
			/**
			 * @brief Get the buffer casted in uint64_t*
			 * @return Pointer on the buffer with correct cast.
			 */
			uint64_t* getDataU64(void) {
				return (uint64_t*)m_data;
			}
			
			/**
			 * @brief Get the buffer casted in float*
			 * @return Pointer on the buffer with correct cast.
			 */
			float* getDataF(void) {
				return (float*)m_data;
			}
			/**
			 * @brief Get the buffer casted in double*
			 * @return Pointer on the buffer with correct cast.
			 */
			double* getDataD(void) {
				return (double*)m_data;
			}
	};
};

#endif


