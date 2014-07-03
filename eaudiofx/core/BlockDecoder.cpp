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
#include <eaudiofx/core/BufferAudioRaw.h>
#include <eaudiofx/core/BlockDecoder.h>



eaudiofx::BlockDecoder::BlockDecoder() :
  m_nbSampleIn(0) {
	setType(eaudiofx::blockTypeDecoder);
	// set input :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "in",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioInput,
	      "{ type:'bitstream', format:'file', extention:['wav','ogg'] }"
	    ) ) );
	// set output :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "out",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioOutput,
	      "{ type:'audio', compression:'raw', frequency:48000, channel:2, format:'float' }",
	      new eaudiofx::BufferAudioRaw(*this, 48000, 2, 4096)
	    ) ) );
}

int32_t eaudiofx::BlockDecoder::pull(double _currentTime, int32_t _request, float _timeout) {
	auto itOut = m_io.find("out");
	if (itOut == m_io.end()) {
		EAUDIOFX_WARNING("request to pull data with no output !!!");
		return eaudiofx::ERR_FAIL;
	}
	auto itIn = m_io.find("in");
	if (itIn == m_io.end()) {
		EAUDIOFX_WARNING("request to pull data with no Input !!!");
		return eaudiofx::ERR_FAIL;
	}
	eaudiofx::BufferAudioRaw* bufferOut = dynamic_cast<eaudiofx::BufferAudioRaw*>(itOut->second.m_buffer);
	if (bufferOut == NULL) {
		// !! impossible case => a buffer can not be removed ...
		EAUDIOFX_ERROR("Buffer has been removed... OR change type ...");
		return eaudiofx::ERR_FAIL;
	}
	//request outpuffer needed size :
	bufferOut->setProperty(48000, 2, _request);
	float* dataOut = bufferOut->getData();
	int32_t offset = 0;
	//EAUDIOFX_DEBUG("Request data : " << (_request*2) );
	while (1) {
		int32_t nbSampleToCopy = std::min(m_nbSampleIn, _request*2 - offset);
		if (m_nbSampleIn > 0) {
			// no pull needed ==> just copy data to output ...
			for (int32_t iii=0; iii < nbSampleToCopy; ++iii) {
				dataOut[offset + iii] = m_tmpBuffer[iii];
			}
			offset += nbSampleToCopy;
			m_nbSampleIn -= nbSampleToCopy;
			if (m_nbSampleIn > 0) {
				// some data in the buffer ==> move it ...
				for (int32_t iii=0; iii < MAX_DATA_IN_BUFFER-nbSampleToCopy; ++iii) {
					m_tmpBuffer[iii] = m_tmpBuffer[nbSampleToCopy+iii];
				}
			} else {
				m_nbSampleIn = 0;
			}
			if (offset == _request*2) {
				// putput have enought data
				return eaudiofx::ERR_NONE;
			}
		}
		
		// Request block input:
		int32_t ret = eaudiofx::Block::pull(_currentTime, 256, _timeout);
		
		if (ret != eaudiofx::ERR_NONE) {
			EAUDIOFX_ERROR("can not get data ...");
			return -1;
		}
		eaudiofx::BufferStream* bufferIn = dynamic_cast<eaudiofx::BufferStream*>(itIn->second.m_buffer);
		if (bufferIn == NULL) {
			// !! impossible case => a buffer can not be removed ...
			EAUDIOFX_ERROR("Buffer has been removed... OR change type ...");
			return eaudiofx::ERR_FAIL;
		}
		if (bufferIn->setAvaillableSize() == 0) {
			for (size_t iii=0; iii<64; ++iii) {
				m_tmpBuffer[m_nbSampleIn] = 0.0f;
				m_nbSampleIn++;
				m_tmpBuffer[m_nbSampleIn] = 0.0f;
				m_nbSampleIn++;
			}
		}
		if (true == true) {
			// wav input :
			// TODO : Do it better ...
			size_t provideData = bufferIn->setAvaillableSize();
			int16_t* inputData = (int16_t*)bufferIn->getData();
			for (size_t iii=0; iii<provideData/2; ++iii) {
				m_tmpBuffer[m_nbSampleIn] = ((double)inputData[iii]) * 0.000030518; // 1/32768
				m_nbSampleIn++;
				m_tmpBuffer[m_nbSampleIn] = ((double)inputData[iii]) * 0.000030518; // 1/32768
				m_nbSampleIn++;
			}
		}
		//EAUDIOFX_DEBUG("internal FIFO : " << m_nbSampleIn );
	}
	return eaudiofx::ERR_NONE;
}


int32_t eaudiofx::BlockDecoder::init() {
	
	return eaudiofx::ERR_NONE;
}


int32_t eaudiofx::BlockDecoder::unInit() {
	
	return eaudiofx::ERR_NONE;
}


