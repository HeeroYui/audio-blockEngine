/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/base/ReceiverRiver.h>
#include <eaudiofx/core/BufferAudio.h>


#undef __class__
#define __class__ "ReceiverRiver"


int32_t eaudiofx::ReceiverRiver::algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
	EAUDIOFX_INFO("Process: " << _currentTime << " chunkTime=" << _processTimeSlot);
	return eaudiofx::ERR_NONE;
}


void eaudiofx::ReceiverRiver::init() {
	eaudiofx::Block::init();
	
}

eaudiofx::ReceiverRiver::ReceiverRiver() :
  m_processStarted(false),
  m_input(*this, "in", "Input audio flow", "{ type:'audio', freq:[8000, 16000, 32000, 48000, 64000, 96000, 128000, 192000], format:['int8','int16','int32','float']}") {
	addObjectType("eaudiofx::ReceiverRtAudio");
};


void eaudiofx::ReceiverRiver::onDataNeeded(void* _data,
                                           const std11::chrono::system_clock::time_point& _time,
                                           size_t _nbChunk,
                                           enum audio::format _format,
                                           uint32_t _frequency,
                                           const std::vector<audio::channel>& _map) {
	if (_format != audio::format_int16) {
		EAUDIOFX_ERROR("call wrong type ... (need int16_t)");
	}
	int16_t* data = static_cast<int16_t*>(_data);
	
	int32_t nbData = std::min(m_buffer.size()/2, _nbChunk*2);
	for (int32_t iii=0; iii<nbData*2; ++iii) {
		((int8_t*)_data)[iii] = m_buffer[iii];
		//EAUDIOFX_ERROR("write : " << data[iii]);
	}
}

int32_t eaudiofx::ReceiverRiver::algoInit() {
	EAUDIOFX_DEBUG("Intanciate audio::river Manager ...");
	m_manager = audio::river::Manager::create("eaudio-fx-output");
	if (m_manager == nullptr) {
		EAUDIOFX_ERROR("Can not intanciate RIVER interface");
		return eaudiofx::ERR_FAIL;
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
		EAUDIOFX_ERROR("nullptr interface");
		return eaudiofx::ERR_FAIL;
	}
	// set callback mode ...
	m_interface->setOutputCallback(std11::bind(&ReceiverRiver::onDataNeeded,
	                                           this,
	                                           std11::placeholders::_1,
	                                           std11::placeholders::_2,
	                                           std11::placeholders::_3,
	                                           std11::placeholders::_4,
	                                           std11::placeholders::_5,
	                                           std11::placeholders::_6));
	m_interface->start();
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRiver::algoUnInit() {
	EAUDIOFX_DEBUG("un-init Stream ...");
	if(m_interface == nullptr) {
		EAUDIOFX_ERROR("nullptr interface");
		return eaudiofx::ERR_FAIL;
	}
	m_interface.reset();
	m_manager.reset();
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRiver::algoStart() {
	EAUDIOFX_DEBUG("Start stream ...");
	if(m_interface == nullptr) {
		EAUDIOFX_ERROR("nullptr interface");
		return eaudiofx::ERR_FAIL;
	}
	m_interface->start();
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverRiver::algoStop() {
	EAUDIOFX_DEBUG("Stop Stream ...");
	if(m_interface == nullptr) {
		EAUDIOFX_ERROR("nullptr interface");
		return eaudiofx::ERR_FAIL;
	}
	m_interface->stop();
	return eaudiofx::ERR_NONE;
};

