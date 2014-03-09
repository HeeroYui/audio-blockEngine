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
			BufferAudioRaw(eaudiofx::Block& _parent);
			BufferAudioRaw(eaudiofx::Block& _parent, int32_t _frequency, int32_t _nbChannel, int32_t _nbSample = -1);
			virtual ~BufferAudioRaw(void) {};
		protected:
			size_t m_allocatedSample; //!< generate with m_allocatedBytes/sizeof(**m_audioFormat**) / m_nbChannel;
		protected:
			size_t m_size; //!< number of sample for each channels provided in this buffer ... (write by the upstream (can be 0))
		protected:
			size_t m_sizeRequested; //!< in pull mode, number of sample for each channels requested by the next Filter
		public:
			void setProperty(int32_t _frequency, int32_t _nbChannel, int32_t _nbSample);
	};
};

#endif


