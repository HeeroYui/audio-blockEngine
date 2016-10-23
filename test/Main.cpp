/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <etk/types.hpp>
#include <ewol/ewol.hpp>
#include <gale/context/commandLine.hpp>

#include <test/debug.hpp>
#include <test/Windows.hpp>
#include <ewol/object/Object.hpp>
#include <ewol/widget/Manager.hpp>
#include <ewol/context/Context.hpp>

class MainApplication : public ewol::context::Application {
	public:
		virtual void onCreate(ewol::Context& _context) override {
			APPL_INFO("==> OnCreate APPL (START) [" << gale::getBoardType() << "] (" << gale::getCompilationMode() << ")");
			for( int32_t iii=0 ; iii<_context.getCmd().size(); iii++) {
				std::string tmpppp = _context.getCmd().get(iii);
				if (    tmpppp == "-h"
				     || tmpppp == "--help") {
					APPL_INFO("  -t c-flags-file-name" );
					APPL_INFO("  -h/--help display this help" );
					exit(0);
				}
			}
			_context.setTitle("test 'block-engine'");
			_context.setSize(vec2(800, 600));
			
			// select internal data for font ...
			_context.getFontDefault().setUseExternal(false);
			_context.getFontDefault().set("FreeSerif", 30);
		}
		
		void onStart(ewol::Context& _context) override {
			APPL_INFO("==> On start APPL (END)");
			ewol::widget::WindowsShared basicWindows = appl::Windows::create();
			// create the specific windows
			_context.setWindows(basicWindows);
			APPL_INFO("==> On start APPL (END)");
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
