/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <eaudiofx/core/BlockGenerator.hpp>
#include <etk/os/FSNode.hpp>

namespace eaudiofx {
	class GeneratorFile : public eaudiofx::BlockGenerator {
		public:
			GeneratorFile();
			virtual ~GeneratorFile() {};
		protected:
			etk::FSNode* m_file;
		public: // herieted function :
			virtual int32_t pull(double _currentTime, int32_t _request, float _timeout);
			virtual int32_t init();
			virtual int32_t unInit();
	};
};



