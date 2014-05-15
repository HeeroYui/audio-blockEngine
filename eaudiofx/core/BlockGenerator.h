/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_GENERATOR_H__
#define __EAUDIOFX_BLOCK_GENERATOR_H__

#include <eaudiofx/core/Block.h>

namespace eaudiofx {
	class BlockGenerator : public eaudiofx::Block {
		public:
			BlockGenerator();
			virtual ~BlockGenerator() {};
		private:
			bool m_isLive; //!< a generator mark as a live element is manage by an external event system like IO interuption
		public:
			/**
			 * @brief Get if the genertor is a live stream
			 * @return true This is a live stream
			 * @return false This is not a live stream
			 */
			bool getLive() {
				return m_isLive;
			}
			/**
			 * @brief Set the new status of live stream.
			 * @param[in] _isLive status requested.
			 */
			void setLive(bool _isLive=true) {
				m_isLive = _isLive;
			}
		
	};
};

#endif


