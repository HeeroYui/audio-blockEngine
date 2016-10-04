/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <eaudiofx/core/BufferAudio.hpp>

namespace eaudiofx {
	class BufferAudioFreq : public eaudiofx::BufferAudio {
		public:
			BufferAudioFreq(eaudiofx::Block& _parent);
			virtual ~BufferAudioFreq() {};
	};
};


