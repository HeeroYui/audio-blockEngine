/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <eaudiofx/core/BlockGenerator.hpp>

namespace eaudiofx {
	class GeneratorRiver : public eaudiofx::BlockGenerator {
		public:
			GeneratorRiver();
			virtual ~GeneratorRiver() {};
		public:
			int32_t pull(double _currentTime, int32_t _request, float _timeout);
	};
};



