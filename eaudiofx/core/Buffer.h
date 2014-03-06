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

namespace eaudiofx {
	class Buffer {
		public:
			Buffer(void) {};
			~Buffer(void) {};
		protected:
			double m_timestamp; //!< current buffer time;
			double m_time; //!< current buffer data time size;
	};
};

#endif


