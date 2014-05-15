/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/base/GeneratorRtAudio.h>
#include <eaudiofx/core/BufferAudioRaw.h>
#include <airtaudio/Interface.h>

eaudiofx::GeneratorRtAudio::GeneratorRtAudio() {
	setLive(true);
	// set output :
	m_io.insert(
	  std::pair<std::string, eaudiofx::Block::IOProperty>(
	    "out",
	    eaudiofx::Block::IOProperty(
	      eaudiofx::Block::ioOutput,
	      "",
	      new eaudiofx::BufferAudioRaw(*this, 48000, 2)
	    ) ) );
	
};


