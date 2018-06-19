/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/base/ReceiverFile.hpp>


audio::blockEngine::ReceiverFile::ReceiverFile() :
  m_file(null),
  m_channels(4),
  m_frequency(16000),
  m_requestSize(256),
  m_processStarted(false) {
	// set input :
	m_io.insert(
	  etk::Pair<etk::String, audio::blockEngine::Block::IOProperty>(
	    "in",
	    audio::blockEngine::Block::IOProperty(
	      audio::blockEngine::Block::ioInput,
	      "{ type:'audio', compression:'raw', frequency:16000, channel:4, format:'int16_t' }",
	      null
	    ) ) );
}


int32_t audio::blockEngine::ReceiverFile::init() {
	m_file = new etk::FSNode("ouput.raw");
	if (m_file == null) {
		ABE_ERROR("Can not allocate the output file ...");
		return audio::blockEngine::ERR_FAIL;
	}
	if (m_file->fileOpenWrite() == false) {
		ABE_ERROR("Can not open the output file ...");
		return audio::blockEngine::ERR_FAIL;
	}
	return audio::blockEngine::ERR_NONE;
};

int32_t audio::blockEngine::ReceiverFile::unInit() {
	ABE_DEBUG("un-init Stream ...");
	if (m_file == null) {
		return audio::blockEngine::ERR_NONE;
	}
	if (m_file->fileClose() == false) {
		ABE_ERROR("Can not close the input file ...");
		delete(m_file);
		m_file = null;
		return audio::blockEngine::ERR_FAIL;
	}
	delete(m_file);
	m_file = null;
	return audio::blockEngine::ERR_NONE;
};

int32_t audio::blockEngine::ReceiverFile::start() {
	ABE_DEBUG("Start stream ...");
	m_processStarted = true;
	return audio::blockEngine::ERR_NONE;
};

int32_t audio::blockEngine::ReceiverFile::stop() {
	ABE_DEBUG("Stop Stream ...");
	m_processStarted = false;
	return audio::blockEngine::ERR_NONE;
};

/*
int32_t audio::blockEngine::ReceiverFile::pull(double _currentTime, int32_t _request, float _timeout) {
	auto it = m_io.find("out");
	if (it == m_io.end()) {
		ABE_WARNING("request to pull data with no output !!!");
		return audio::blockEngine::ERR_FAIL;
	}
	audio::blockEngine::BufferStream* buffer = dynamic_cast<audio::blockEngine::BufferStream*>(it->second.m_buffer);
	//ABE_ERROR("Generate data, request : " << _request << " at time : " << _currentTime);
	if (buffer == null) {
		// !! impossible case => a buffer can not be removed ...
		ABE_ERROR("Buffer has been removed... OR change type ...");
		return audio::blockEngine::ERR_FAIL;
	}
	//request outpuffer needed size :
	buffer->setProperty(_request);
	uint8_t* data = buffer->getData();
	if (m_file == null) {
		ABE_ERROR("Buffer output error ==> !!ERROR!!");
		return audio::blockEngine::ERR_FAIL;
	}
	int64_t nbRead = m_file->fileRead(data, sizeof(uint8_t), _request);
	buffer->setAvaillableSize(nbRead);
	return audio::blockEngine::ERR_NONE;
}
*/
