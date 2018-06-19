/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/base/GeneratorSignal.hpp>
#include <audio/blockEngine/core/BufferStream.hpp>
#include <audio/blockEngine/base/GeneratorFile.hpp>



audio::blockEngine::GeneratorFile::GeneratorFile() :
  m_file(null) {
	// set output :
	m_io.insert(
	  etk::Pair<etk::String, audio::blockEngine::Block::IOProperty>(
	    "out",
	    audio::blockEngine::Block::IOProperty(
	      audio::blockEngine::Block::ioOutput,
	      "{ type:'bitstream', format:'file' }",
	      new audio::blockEngine::BufferStream(*this)
	    ) ) );
	
}

int32_t audio::blockEngine::GeneratorFile::pull(double _currentTime, int32_t _request, float _timeout) {
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


int32_t audio::blockEngine::GeneratorFile::init() {
	m_file = new etk::FSNode("DATA:menu.wav");
	if (m_file == null) {
		ABE_ERROR("Can not allocate the input file ...");
		return audio::blockEngine::ERR_FAIL;
	}
	if (m_file->fileOpenRead() == false) {
		ABE_ERROR("Can not open the input file ...");
		return audio::blockEngine::ERR_FAIL;
	}
	return audio::blockEngine::ERR_NONE;
}


int32_t audio::blockEngine::GeneratorFile::unInit() {
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
}


