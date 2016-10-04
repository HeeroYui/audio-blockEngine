/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/base/GeneratorRtAudio.hpp>
#include <audio/blockEngine/core/BufferAudioRaw.hpp>
#include <airtaudio/Interface.hpp>

audio::blockEngine::GeneratorRiver::GeneratorRiver() {
	setLive(true);
	// set output :
	m_io.insert(
	  std::pair<std::string, audio::blockEngine::Block::IOProperty>(
	    "out",
	    audio::blockEngine::Block::IOProperty(
	      audio::blockEngine::Block::ioOutput,
	      "",
	      new audio::blockEngine::BufferAudioRaw(*this, 48000, 2)
	    ) ) );
	
};


