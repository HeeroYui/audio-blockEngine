/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/core/Processing.hpp>
#include <unistd.h>

audio::blockEngine::Processing::Processing() {
	addObjectType("audio::blockEngine::Processing");
};

int32_t audio::blockEngine::Processing::process() {
	ABE_INFO("Start process : '" << propertyName << "'");
	return audio::blockEngine::ERR_NONE;
}

int32_t audio::blockEngine::Processing::start() {
	audio::blockEngine::Thread::start();
	return audio::blockEngine::ERR_NONE;
}

int32_t audio::blockEngine::Processing::stop() {
	audio::blockEngine::Thread::stop();
	return audio::blockEngine::ERR_NONE;
}

int32_t audio::blockEngine::Processing::waitEndOfProcess() {
	ABE_INFO("wait end of Processing : '" << propertyName << "'");
	return audio::blockEngine::ERR_NONE;
}


bool audio::blockEngine::Processing::stateStart() {
	ABE_INFO("Start Processing : '" << propertyName << "'");
	// TODO : Add return code ... and test all of theses events ...
	ABE_ERROR("======================================");
	// Init request flow update:
	flowLinkInput();
	ABE_ERROR("======================================");
	// check if the IOs are compatible
	flowCheckAllCompatibility();
	ABE_ERROR("======================================");
	// Allocate all Outputs
	flowAllocateOutput();
	ABE_ERROR("======================================");
	// Get pointer on all Inputs
	flowGetInput();
	ABE_ERROR("======================================");
	// init algorithm
	int32_t ret = algoInit();
	if (ret != audio::blockEngine::ERR_NONE) {
		return ret;
	}
	audio::blockEngine::BlockMeta::algoStart();
	return false;
}

bool audio::blockEngine::Processing::stateRun() {
	ABE_INFO("Process : '" << propertyName << "'");
	usleep(10000);
	return false;
}

bool audio::blockEngine::Processing::stateStop() {
	ABE_INFO("Stop Processing : '" << propertyName << "'");
	int32_t ret = audio::blockEngine::BlockMeta::algoStop();
	if (ret != audio::blockEngine::ERR_NONE) {
		return ret;
	}
	algoUnInit();
	return false;
}

