/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_GENERATOR_FILE_H__
#define __EAUDIOFX_GENERATOR_FILE_H__

#include <eaudiofx/core/BlockGenerator.h>
#include <etk/os/FSNode.h>

namespace eaudiofx {
	class GeneratorFile : public eaudiofx::BlockGenerator {
		public:
			GeneratorFile(void);
			virtual ~GeneratorFile(void) {};
		protected:
			etk::FSNode* m_file;
		public: // herieted function :
			virtual int32_t pull(double _currentTime, int32_t _request, float _timeout);
			virtual int32_t init(void);
			virtual int32_t unInit(void);
	};
};

#endif


