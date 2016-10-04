/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <ewol/widget/Windows.hpp>
#include <ewol/widget/Composer.hpp>
#include <eaudiofx/core/Processing.hpp>

namespace appl {
	class Windows : public ewol::widget::Windows {
		private:
			ewol::widget::ComposerShared m_composer;
		protected:
			Windows();
			void init();
		public:
			DECLARE_FACTORY(Windows);
		public: // callback functions
			void onCallbackPlay();
			void onCallbackStop();
			void onCallbackPlayStop();
			ememory::SharedPtr<eaudiofx::Processing> m_process;
	};
}


