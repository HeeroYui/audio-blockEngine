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
#include <eaudiofx/eaudiofx.h>

#include <eaudiofx/base/GeneratorFile.h>
#include <eaudiofx/core/BlockDecoder.h>
#include <eaudiofx/base/GeneratorSignal.h>
#include <eaudiofx/base/ReceiverRtAudio.h>

#undef __class__
#define __class__ "Windows"

static const char* const g_eventPlay1 = "appl-play-1";
static const char* const g_eventPlay2 = "appl-play-2";

appl::Windows::Windows() {
	addObjectType("appl::Windows");
}

void appl::Windows::init() {
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
	
	m_composer = ewol::widget::Composer::create(ewol::widget::Composer::String, composition);
	if (m_composer == NULL) {
		APPL_CRITICAL(" An error occured ... in the windows creatrion ...");
		return;
	}
	setSubWidget(m_composer);
	m_composer->registerOnEventNameWidget(shared_from_this(), "bt-play1", "pressed", g_eventPlay1);
	m_composer->registerOnEventNameWidget(shared_from_this(), "bt-play2", "pressed", g_eventPlay2);
}

eaudiofx::Processing* process = NULL;

void appl::Windows::onReceiveMessage(const ewol::object::Message& _msg) {
	if (_msg.getMessage() == g_eventPlay1) {
		#if 0
			APPL_INFO("Play Requested ...");
			process = new eaudiofx::Processing();
			if (process == NULL) {
				APPL_ERROR("can not create processing ...");
				return;
			}
			APPL_INFO("Create Generator ...");
			eaudiofx::GeneratorSignal* generator = new eaudiofx::GeneratorSignal();
			if (generator == NULL) {
				APPL_ERROR("can not create Generator ...");
				return;
			}
			generator->setName("myGenerator");
			process->addBlock(generator);
			APPL_INFO("Create Receiver ...");
			eaudiofx::ReceiverRtAudio* receiver = new eaudiofx::ReceiverRtAudio();
			if (receiver == NULL) {
				APPL_ERROR("can not create Receiver ...");
				return;
			}
			receiver->setName("myReceiver");
			process->addBlock(receiver);
			
			process->linkBlock("myGenerator", "out","myReceiver", "in");
			
			process->start();
			return;
		#else
			APPL_INFO("Play Requested ...");
			process = new eaudiofx::Processing();
			if (process == NULL) {
				APPL_ERROR("can not create processing ...");
				return;
			}
			APPL_INFO("Create Generator ...");
			eaudiofx::GeneratorFile* generator = new eaudiofx::GeneratorFile();
			if (generator == NULL) {
				APPL_ERROR("can not create Generator ...");
				return;
			}
			generator->setName("myGenerator");
			process->addBlock(generator);
			
			APPL_INFO("Create DECODER ...");
			eaudiofx::BlockDecoder* decoder = new eaudiofx::BlockDecoder();
			if (decoder == NULL) {
				APPL_ERROR("can not create Generator ...");
				return;
			}
			decoder->setName("myDecoder");
			process->addBlock(decoder);
			
			APPL_INFO("Create Receiver ...");
			eaudiofx::ReceiverRtAudio* receiver = new eaudiofx::ReceiverRtAudio();
			if (receiver == NULL) {
				APPL_ERROR("can not create Receiver ...");
				return;
			}
			receiver->setName("myReceiver");
			process->addBlock(receiver);
			
			process->linkBlock("myGenerator", "out","myDecoder", "in");
			process->linkBlock("myDecoder", "out","myReceiver", "in");
			
			process->start();
			return;
		#endif
	}
	if (_msg.getMessage() == g_eventPlay2) {
		if (process != NULL) {
			process->stop();
		}
		return;
	}
}

