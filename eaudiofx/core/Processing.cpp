/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/core/Processing.h>
#include <unistd.h>


int32_t eaudiofx::Processing::process() {
	EAUDIOFX_INFO("Start process : '" << getName() << "'");
	return eaudiofx::ERR_NONE;
}

int32_t eaudiofx::Processing::start() {
	eaudiofx::Thread::start();
	return eaudiofx::ERR_NONE;
}

int32_t eaudiofx::Processing::stop() {
	eaudiofx::Thread::stop();
	return eaudiofx::ERR_NONE;
}

int32_t eaudiofx::Processing::waitEndOfProcess() {
	EAUDIOFX_INFO("wait end of Processing : '" << getName() << "'");
	return eaudiofx::ERR_NONE;
}


bool eaudiofx::Processing::stateStart() {
	EAUDIOFX_INFO("Start Processing : '" << getName() << "'");
	int32_t ret = algoInit();
	if (ret != eaudiofx::ERR_NONE) {
		return ret;
	}
	eaudiofx::BlockMeta::algoStart();
	return false;
}

bool eaudiofx::Processing::stateRun() {
	EAUDIOFX_INFO("Process : '" << getName() << "'");
	usleep(10000);
	return false;
}

bool eaudiofx::Processing::stateStop() {
	EAUDIOFX_INFO("Stop Processing : '" << getName() << "'");
	int32_t ret = eaudiofx::BlockMeta::algoStop();
	if (ret != eaudiofx::ERR_NONE) {
		return ret;
	}
	algoUnInit();
	return false;
}

