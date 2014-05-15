/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/core/Processing.h>


int32_t eaudiofx::Processing::process() {
	EAUDIOFX_INFO("Start process : '" << getName() << "'");
	return eaudiofx::ERR_NONE;
}

int32_t eaudiofx::Processing::start() {
	EAUDIOFX_INFO("Start Processing : '" << getName() << "'");
	int32_t ret = init();
	if (ret != eaudiofx::ERR_NONE) {
		return ret;
	}
	return eaudiofx::BlockMeta::start();
}

int32_t eaudiofx::Processing::stop() {
	EAUDIOFX_INFO("Stop Processing : '" << getName() << "'");
	int32_t ret = eaudiofx::BlockMeta::stop();
	if (ret != eaudiofx::ERR_NONE) {
		return ret;
	}
	return unInit();
}

int32_t eaudiofx::Processing::waitEndOfProcess() {
	EAUDIOFX_INFO("wait end of Processing : '" << getName() << "'");
	return eaudiofx::ERR_NONE;
}