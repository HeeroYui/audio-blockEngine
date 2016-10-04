/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <eaudiofx/core/audio.hpp>
#include <eaudiofx/core/Block.hpp>

namespace eaudiofx {
	class Block;
	class Buffer : public ememory::EnableSharedFromThis<Buffer> {
		public:
			Buffer(eaudiofx::Block& _parent);
			virtual ~Buffer() {};
		protected:
			eaudiofx::Block& m_parent; //!< parrent Block of this Buffer
		protected:
			int64_t m_timestamp; //!< current buffer time
			int64_t m_timeSize; //!< current buffer data time size
	};
};



