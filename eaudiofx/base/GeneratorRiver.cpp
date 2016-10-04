/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <eaudiofx/base/GeneratorRtAudio.hpp>
#include <eaudiofx/core/BufferAudioRaw.hpp>
#include <airtaudio/Interface.hpp>

eaudiofx::GeneratorRiver::GeneratorRiver() {
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


