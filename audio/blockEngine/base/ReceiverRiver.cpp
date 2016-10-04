/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/base/ReceiverRiver.hpp>
#include <audio/blockEngine/core/BufferAudio.hpp>


int32_t audio::blockEngine::ReceiverRiver::algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
	ABE_INFO("Process: " << _currentTime << " chunkTime=" << _processTimeSlot);
	return audio::blockEngine::ERR_NONE;
}


void audio::blockEngine::ReceiverRiver::init() {
	audio::blockEngine::Block::init();
	
}

audio::blockEngine::ReceiverRiver::ReceiverRiver() :
  m_processStarted(false),
  m_input(*this, "in", "Input audio flow", "{ type:'audio', freq:[8000, 16000, 32000, 48000, 64000, 96000, 128000, 192000], format:['int8','int16','int32','float']}") {
	addObjectType("audio::blockEngine::ReceiverRtAudio");
};


void audio::blockEngine::ReceiverRiver::onDataNeeded(void* _data,
                                           const audio::Time& _time,
                                           size_t _nbChunk,
                                           enum audio::format _format,
                                           uint32_t _frequency,
                                           const std::vector<audio::channel>& _map) {
	if (_format != audio::format_int16) {
		ABE_ERROR("call wrong type ... (need int16_t)");
	}
	int16_t* data = static_cast<int16_t*>(_data);
	
	int32_t nbData = std::min(m_buffer.size()/2, _nbChunk*2);
	for (int32_t iii=0; iii<nbData*2; ++iii) {
		((int8_t*)_data)[iii] = m_buffer[iii];
		//ABE_ERROR("write : " << data[iii]);
	}
}

int32_t audio::blockEngine::ReceiverRiver::algoInit() {
	ABE_DEBUG("Intanciate audio::river Manager ...");
	m_manager = audio::river::Manager::create("eaudio-fx-output");
	if (m_manager == nullptr) {
		ABE_ERROR("Can not intanciate RIVER interface");
		return audio::blockEngine::ERR_FAIL;
	}
	//Set stereo output:
	std::vector<audio::channel> channelMap;
	channelMap.push_back(audio::channel_frontLeft);
	channelMap.push_back(audio::channel_frontRight);
	m_interface = m_manager->createOutput(48000,
	                                      channelMap,
	                                      audio::format_int16,
	                                      "speaker");
	if(m_interface == nullptr) {
		ABE_ERROR("nullptr interface");
		return audio::blockEngine::ERR_FAIL;
	}
	// set callback mode ...
	m_interface->setOutputCallback(std::bind(&ReceiverRiver::onDataNeeded,
	                                           this,
	                                           std::placeholders::_1,
	                                           std::placeholders::_2,
	                                           std::placeholders::_3,
	                                           std::placeholders::_4,
	                                           std::placeholders::_5,
	                                           std::placeholders::_6));
	m_interface->start();
	return audio::blockEngine::ERR_NONE;
};

int32_t audio::blockEngine::ReceiverRiver::algoUnInit() {
	ABE_DEBUG("un-init Stream ...");
	if(m_interface == nullptr) {
		ABE_ERROR("nullptr interface");
		return audio::blockEngine::ERR_FAIL;
	}
	m_interface.reset();
	m_manager.reset();
	return audio::blockEngine::ERR_NONE;
};

int32_t audio::blockEngine::ReceiverRiver::algoStart() {
	ABE_DEBUG("Start stream ...");
	if(m_interface == nullptr) {
		ABE_ERROR("nullptr interface");
		return audio::blockEngine::ERR_FAIL;
	}
	m_interface->start();
	return audio::blockEngine::ERR_NONE;
};

int32_t audio::blockEngine::ReceiverRiver::algoStop() {
	ABE_DEBUG("Stop Stream ...");
	if(m_interface == nullptr) {
		ABE_ERROR("nullptr interface");
		return audio::blockEngine::ERR_FAIL;
	}
	m_interface->stop();
	return audio::blockEngine::ERR_NONE;
};

