/**
 * @author Edouard DUPIN
 * 
 * @copyright 2010, Edouard DUPIN, all right reserved
 * 
 * @license BSD 3 clauses (see license file)
 */


#include <etk/types.h>
#include <ewol/ewol.h>
#include <ewol/context/commandLine.h>

#include <test/debug.h>
#include <test/Windows.h>
#include <ewol/object/Object.h>
#include <ewol/widget/Manager.h>
#include <ewol/context/Context.h>

class MainApplication : public ewol::context::Application {
	public:
		bool init(ewol::Context& _context, size_t _initId) {
			APPL_INFO("==> Init APPL (START) [" << ewol::getBoardType() << "] (" << ewol::getCompilationMode() << ")");
			
			// TODO : Remove this : Move if in the windows properties
			_context.setSize(vec2(800, 600));
			
			// select internal data for font ...
			_context.getFontDefault().setUseExternal(false);
			_context.getFontDefault().set("FreeSerif", 30);
			
			ewol::object::Shared<ewol::widget::Windows> basicWindows = ewol::object::makeShared(new appl::Windows());
			// create the specific windows
			_context.setWindows(basicWindows);
			APPL_INFO("==> Init APPL (END)");
			return true;
		}
		
		void unInit(ewol::Context& _context) {
			APPL_INFO("==> Un-Init APPL (START)");
			// nothing to do ...
			APPL_INFO("==> Un-Init APPL (END)");
		}
};


/**
 * @brief Main of the program (This can be set in every case, but it is not used in Andoid...).
 * @param std IO
 * @return std IO
 */
int main(int _argc, const char *_argv[]) {
	// second possibility
	return ewol::run(new MainApplication(), _argc, _argv);
}
