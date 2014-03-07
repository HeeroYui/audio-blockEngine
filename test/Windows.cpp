/**
 * @author Edouard DUPIN
 * 
 * @copyright 2010, Edouard DUPIN, all right reserved
 * 
 * @license BSD 3 clauses (see license file)
 */

#include <ewol/ewol.h>
#include <test/debug.h>
#include <test/Windows.h>
#include <ewol/widget/Label.h>
#include <etk/tool.h>

#undef __class__
#define __class__ "Windows"

static const char* const g_eventPlay1 = "appl-play-1";
static const char* const g_eventPlay2 = "appl-play-2";

appl::Windows::Windows(void) :
  m_composer(NULL) {
	setTitle("example 001_HelloWord");
	std::string composition = std::string("");
	composition += "<sizer mode='vert'>\n";
	composition += "	<sizer mode='hori'>\n";
	composition += "		<button name='bt-play1'>\n";
	composition += "			<label>\n";
	composition += "				Play 1\n";
	composition += "			</label>\n";
	composition += "		</button>\n";
	composition += "		<button name='bt-play2'>\n";
	composition += "			<label>\n";
	composition += "				Play 2\n";
	composition += "			</label>\n";
	composition += "		</button>\n";
	composition += "	</sizer>\n";
	composition += "	<spacer expand='true' fill='true'/>\n";
	composition += "</sizer>\n";
	
	m_composer = new ewol::widget::Composer(ewol::widget::Composer::String, composition);
	if (m_composer == NULL) {
		APPL_CRITICAL(" An error occured ... in the windows creatrion ...");
		return;
	}
	setSubWidget(m_composer);
	m_composer->registerOnEventNameWidget(this, "bt-play1", "pressed", g_eventPlay1);
	m_composer->registerOnEventNameWidget(this, "bt-play2", "pressed", g_eventPlay2);
}


void appl::Windows::onObjectRemove(ewol::Object * _removeObject) {
	if (_removeObject == m_composer) {
		m_composer = NULL;
		markToRedraw();
		return;
	}
}


void appl::Windows::onReceiveMessage(const ewol::object::Message& _msg) {
	if (_msg.getMessage() == g_eventChangeValues) {
		
		return;
	}
	if (_msg.getMessage() == g_eventAutoMode) {
		
		return;
	}
}

