/**
 * @author Edouard DUPIN
 * 
 * @copyright 2010, Edouard DUPIN, all right reserved
 * 
 * @license BSD 3 clauses (see license file)
 */

#ifndef __APPL_WINDOWS_H__
#define __APPL_WINDOWS_H__

#include <ewol/widget/Windows.h>
#include <ewol/widget/Composer.h>

namespace appl {
	class Windows : public ewol::widget::Windows {
		private:
			ewol::widget::Composer* m_composer;
		public:
			Windows();
		public: // herited functions
			virtual void onReceiveMessage(const ewol::object::Message& _msg);
	};
};


#endif