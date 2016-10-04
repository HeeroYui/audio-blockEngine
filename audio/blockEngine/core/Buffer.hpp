/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <audio/blockEngine/core/audio.hpp>
#include <audio/blockEngine/core/Block.hpp>
namespace audio {
	namespace blockEngine {
		class Block;
		class Buffer : public ememory::EnableSharedFromThis<Buffer> {
			public:
				Buffer(audio::blockEngine::Block& _parent);
				virtual ~Buffer() {};
			protected:
				audio::blockEngine::Block& m_parent; //!< parrent Block of this Buffer
			protected:
				int64_t m_timestamp; //!< current buffer time
				int64_t m_timeSize; //!< current buffer data time size
		};
	}
}



