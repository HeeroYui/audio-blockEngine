/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <ewol/ewol.hpp>
#include <test/debug.hpp>
#include <test/Windows.hpp>
#include <ewol/widget/Label.hpp>
#include <etk/tool.hpp>
#include <audio/blockEngine/eaudiofx.hpp>
#include <ewol/widget/Button.hpp>
#include <unistd.h>

#include <audio/blockEngine/base/GeneratorSignal.hpp>
#include <audio/blockEngine/base/ReceiverRiver.hpp>


static const char* const g_eventPlay1 = "appl-play-1";
static const char* const g_eventPlay2 = "appl-play-2";

appl::Windows::Windows() {
	addObjectType("appl::Windows");
}

void appl::Windows::init() {
	ewol::widget::Windows::init();
	etk::String composition = etk::String("");
	composition += "<sizer mode='vert'>\n";
	composition += "	<sizer mode='hori'>\n";
	composition += "		<button name='bt-play1'>\n";
	composition += "			<label>\n";
	composition += "				Play 1\n";
	composition += "			</label>\n";
	composition += "		</button>\n";
	composition += "		<button name='bt-stop1'>\n";
	composition += "			<label>\n";
	composition += "				Stop 1\n";
	composition += "			</label>\n";
	composition += "		</button>\n";
	composition += "		<button name='bt-play-stop'>\n";
	composition += "			<label>\n";
	composition += "				Play / Stop\n";
	composition += "			</label>\n";
	composition += "		</button>\n";
	composition += "	</sizer>\n";
	composition += "	<spacer expand='true' fill='true'/>\n";
	composition += "</sizer>\n";
	
	m_composer = ewol::widget::Composer::create();
	if (m_composer == nullptr) {
		APPL_CRITICAL(" An error occured ... in the windows creatrion ...");
		return;
	}
	m_composer->loadFromString(composition);
	setSubWidget(m_composer);
	subBind(ewol::widget::Button, "bt-play1", signalPressed, sharedFromThis(), &appl::Windows::onCallbackPlay);
	subBind(ewol::widget::Button, "bt-stop1", signalPressed, sharedFromThis(), &appl::Windows::onCallbackStop);
	subBind(ewol::widget::Button, "bt-play-stop", signalPressed, sharedFromThis(), &appl::Windows::onCallbackPlayStop);
}

void appl::Windows::onCallbackPlayStop() {
	onCallbackPlay();
	usleep(500000);
	onCallbackStop();
}
void appl::Windows::onCallbackPlay() {
	#if 0
		APPL_INFO("Play Requested ...");
		m_process = audio::blockEngine::Processing::create();
		if (m_process == nullptr) {
			APPL_ERROR("can not create processing ...");
			return;
		}
		APPL_INFO("Create Generator ...");
		ememory::SharedPtr<audio::blockEngine::GeneratorFile> generator = audio::blockEngine::GeneratorFile::create();
		if (generator == nullptr) {
			APPL_ERROR("can not create Generator ...");
			return;
		}
		generator->propertyName.set("myGenerator");
		m_process->addBlock(generator);
		
		APPL_INFO("Create DECODER ...");
		ememory::SharedPtr<audio::blockEngine::BlockDecoder> decoder = audio::blockEngine::BlockDecoder::create();
		if (decoder == nullptr) {
			APPL_ERROR("can not create Generator ...");
			return;
		}
		decoder->propertyName.set("myDecoder");
		m_process->addBlock(decoder);
		
		APPL_INFO("Create Receiver ...");
		ememory::SharedPtr<audio::blockEngine::ReceiverRtAudio> receiver = audio::blockEngine::ReceiverRtAudio::create();
		if (receiver == nullptr) {
			APPL_ERROR("can not create Receiver ...");
			return;
		}
		receiver->propertyName.set("myReceiver");
		m_process->addBlock(receiver);
		
		m_process->linkBlock("myGenerator", "out","myDecoder", "in");
		m_process->linkBlock("myDecoder", "out","myReceiver", "in");
		
		m_process->start();
		return;
	#else
		APPL_INFO("Play Requested ...");
		m_process = audio::blockEngine::Processing::create();
		if (m_process == nullptr) {
			APPL_ERROR("can not create processing ...");
			return;
		}
		m_process->propertyName.set("main Process");
		APPL_INFO("Create Generator Sinus");
		ememory::SharedPtr<audio::blockEngine::GeneratorSignal> generator = audio::blockEngine::GeneratorSignal::create();
		if (generator == nullptr) {
			APPL_ERROR("can not create Generator ...");
			return;
		}
		generator->propertyName.set("myGenerator");
		m_process->addBlock(generator);
		
		APPL_INFO("Create Receiver ...");
		ememory::SharedPtr<audio::blockEngine::ReceiverRiver> receiver = audio::blockEngine::ReceiverRiver::create();
		if (receiver == nullptr) {
			APPL_ERROR("can not create Receiver ...");
			return;
		}
		receiver->propertyName.set("myReceiver");
		m_process->addBlock(receiver);
		
		m_process->linkBlock("myGenerator", "out","myReceiver", "in");
		
		m_process->start();
		return;
	#endif
}

void appl::Windows::onCallbackStop() {
	if (m_process != nullptr) {
		m_process->stop();
	}
}

