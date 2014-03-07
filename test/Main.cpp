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


/**
 * @brief Main of the program (This can be set in every case, but it is not used in Andoid...).
 * @param std IO
 * @return std IO
 */
int main(int argc, const char *argv[]) {
	// only one things to do : 
	return ewol::run(argc, argv);
}

/**
 * @brief main application function Initialisation
 */
bool APP_Init(ewol::Context& _context) {
	APPL_INFO("==> Init APPL (START) [" << ewol::getBoardType() << "] (" << ewol::getCompilationMode() << ")");
	
	// TODO : Remove this : Move if in the windows properties
	_context.setSize(vec2(800, 600));
	
	// select internal data for font ...
	_context.getFontDefault().setUseExternal(true);
	_context.getFontDefault().set("FreeSerif;DejaVuSansMono", 19);
	
	ewol::widget::Windows* basicWindows = new appl::Windows();
	// create the specific windows
	_context.setWindows(basicWindows);
	APPL_INFO("==> Init APPL (END)");
	return true;
}

/**
 * @brief main application function Un-Initialisation
 */
void APP_UnInit(ewol::Context& _context) {
	APPL_INFO("==> Un-Init APPL (START)");
	// Nothing to do (main windows will be remove after this call if not done...
	ewol::widget::Windows* basicWindows = _context.getWindows();
	
	if (NULL != basicWindows) {
		basicWindows->removeObject();
		basicWindows = NULL;
	}
	_context.setWindows(NULL);
	APPL_INFO("==> Un-Init APPL (END)");
}

