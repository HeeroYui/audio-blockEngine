/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#include <eaudiofx/debug.hpp>
#include <eaudiofx/base/ReceiverFile.hpp>


eaudiofx::ReceiverFile::ReceiverFile() :
  m_file(nullptr),
  m_channels(4),
  m_frequency(16000),
  m_requestSize(256),
  m_processStarted(false) {
	// set input :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "in",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioInput,
	      "{ type:'audio', compression:'raw', frequency:16000, channel:4, format:'int16_t' }",
	      nullptr
	    ) ) );
}


int32_t eaudiofx::ReceiverFile::init() {
	m_file = new etk::FSNode("ouput.raw");
	if (m_file == nullptr) {
		EAUDIOFX_ERROR("Can not allocate the output file ...");
		return eaudiofx::ERR_FAIL;
	}
	if (m_file->fileOpenWrite() == false) {
		EAUDIOFX_ERROR("Can not open the output file ...");
		return eaudiofx::ERR_FAIL;
	}
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverFile::unInit() {
	EAUDIOFX_DEBUG("un-init Stream ...");
	if (m_file == nullptr) {
		return eaudiofx::ERR_NONE;
	}
	if (m_file->fileClose() == false) {
		EAUDIOFX_ERROR("Can not close the input file ...");
		delete(m_file);
		m_file = nullptr;
		return eaudiofx::ERR_FAIL;
	}
	delete(m_file);
	m_file = nullptr;
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverFile::start() {
	EAUDIOFX_DEBUG("Start stream ...");
	m_processStarted = true;
	return eaudiofx::ERR_NONE;
};

int32_t eaudiofx::ReceiverFile::stop() {
	EAUDIOFX_DEBUG("Stop Stream ...");
	m_processStarted = false;
	return eaudiofx::ERR_NONE;
};

/*
int32_t eaudiofx::ReceiverFile::pull(double _currentTime, int32_t _request, float _timeout) {
	auto it = m_io.find("out");
	if (it == m_io.end()) {
		EAUDIOFX_WARNING("request to pull data with no output !!!");
		return eaudiofx::ERR_FAIL;
	}
	eaudiofx::BufferStream* buffer = dynamic_cast<eaudiofx::BufferStream*>(it->second.m_buffer);
	//EAUDIOFX_ERROR("Generate data, request : " << _request << " at time : " << _currentTime);
	if (buffer == nullptr) {
		// !! impossible case => a buffer can not be removed ...
		EAUDIOFX_ERROR("Buffer has been removed... OR change type ...");
		return eaudiofx::ERR_FAIL;
	}
	//request outpuffer needed size :
	buffer->setProperty(_request);
	uint8_t* data = buffer->getData();
	if (m_file == nullptr) {
		EAUDIOFX_ERROR("Buffer output error ==> !!ERROR!!");
		return eaudiofx::ERR_FAIL;
	}
	int64_t nbRead = m_file->fileRead(data, sizeof(uint8_t), _request);
	buffer->setAvaillableSize(nbRead);
	return eaudiofx::ERR_NONE;
}
*/
