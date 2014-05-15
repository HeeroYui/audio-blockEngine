/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BUFFER_H__
#define __EAUDIOFX_BUFFER_H__

#include <eaudiofx/core/audio.h>
#include <eaudiofx/core/Block.h>

namespace eaudiofx {
	class Block;
	class Buffer {
		public:
			Buffer(eaudiofx::Block& _parent);
			virtual ~Buffer() {};
		protected:
			eaudiofx::Block& m_parent; //!< parrent Block of this Buffer
		protected:
			double m_timestamp; //!< current buffer time;
			double m_time; //!< current buffer data time size;
		public:
			int32_t pull(double _currentTime, int32_t _request, float _timeout);
		protected:
			bool m_negociated; //!< negiciation status.
		public:
			/**
			 * @brief Get if the IO buffer status is negociated.
			 * @return true if buffer is negosiated.
			 * @return false Not negociated.
			 */
			bool isNegociated() {
				return m_negociated;
			}
			/**
			 * @brief uset the negociation status of the buffer.
			 */
			void requestNewNegociation() {
				m_negociated = false;
			}
	};
};

#endif


