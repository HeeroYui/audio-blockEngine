/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/debug.h>
#include <eaudiofx/base/GeneratorSignal.h>
#include <eaudiofx/core/BufferStream.h>
#include <eaudiofx/base/GeneratorFile.h>



eaudiofx::GeneratorFile::GeneratorFile(void) :
  m_file(NULL) {
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
	if (buffer == NULL) {
		// !! impossible case => a buffer can not be removed ...
		EAUDIOFX_ERROR("Buffer has been removed... OR change type ...");
		return eaudiofx::ERR_FAIL;
	}
	//request outpuffer needed size :
	buffer->setProperty(_request);
	uint8_t* data = buffer->getData();
	if (m_file == NULL) {
		EAUDIOFX_ERROR("Buffer output error ==> !!ERROR!!");
		return eaudiofx::ERR_FAIL;
	}
	int64_t nbRead = m_file->fileRead(data, sizeof(uint8_t), _request);
	buffer->setAvaillableSize(nbRead);
	return eaudiofx::ERR_NONE;
}


int32_t eaudiofx::GeneratorFile::init(void) {
	m_file = new etk::FSNode("DATA:menu.wav");
	if (m_file == NULL) {
		EAUDIOFX_ERROR("Can not allocate the input file ...");
		return eaudiofx::ERR_FAIL;
	}
	if (m_file->fileOpenRead() == false) {
		EAUDIOFX_ERROR("Can not open the input file ...");
		return eaudiofx::ERR_FAIL;
	}
	return eaudiofx::ERR_NONE;
}


int32_t eaudiofx::GeneratorFile::unInit(void) {
	if (m_file == NULL) {
		return eaudiofx::ERR_NONE;
	}
	if (m_file->fileClose() == false) {
		EAUDIOFX_ERROR("Can not close the input file ...");
		delete(m_file);
		m_file = NULL;
		return eaudiofx::ERR_FAIL;
	}
	delete(m_file);
	m_file = NULL;
	return eaudiofx::ERR_NONE;
}


