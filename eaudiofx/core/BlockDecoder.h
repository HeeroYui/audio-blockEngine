/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_DECODER_H__
#define __EAUDIOFX_BLOCK_DECODER_H__

#include <eaudiofx/core/Block.h>

namespace eaudiofx {
	class BlockDecoder : public eaudiofx::Block {
			#define MAX_DATA_IN_BUFFER (8*1024)
		public:
			BlockDecoder(void);
			virtual ~BlockDecoder(void) {};
		public: // herited function
			int32_t pull(double _currentTime, int32_t _request, float _timeout);
			int32_t init(void);
			int32_t unInit(void);
		protected:
			float m_tmpBuffer[MAX_DATA_IN_BUFFER]; //!< internal buffer with data ...
			int32_t m_nbSampleIn; //<! number of sample in the tmpBuffer.
	};
};

#endif


