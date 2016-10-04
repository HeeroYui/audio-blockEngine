/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <eaudiofx/debug.hpp>
#include <eaudiofx/base/GeneratorSignal.hpp>
#include <eaudiofx/core/BufferStream.hpp>
#include <eaudiofx/base/GeneratorFile.hpp>



eaudiofx::GeneratorFile::GeneratorFile() :
  m_file(nullptr) {
	// set output :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "out",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioOutput,
	      "{ type:'bitstream', format:'file' }",
	      new eaudiofx::BufferStream(*this)
	    ) ) );
	
}

int32_t eaudiofx::GeneratorFile::pull(double _currentTime, int32_t _request, float _timeout) {
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


int32_t eaudiofx::GeneratorFile::init() {
	m_file = new etk::FSNode("DATA:menu.wav");
	if (m_file == nullptr) {
		EAUDIOFX_ERROR("Can not allocate the input file ...");
		return eaudiofx::ERR_FAIL;
	}
	if (m_file->fileOpenRead() == false) {
		EAUDIOFX_ERROR("Can not open the input file ...");
		return eaudiofx::ERR_FAIL;
	}
	return eaudiofx::ERR_NONE;
}


int32_t eaudiofx::GeneratorFile::unInit() {
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
}


