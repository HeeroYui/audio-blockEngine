/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/core/Buffer.hpp>

audio::blockEngine::Buffer::Buffer(audio::blockEngine::Block& _parent) :
  m_parent(_parent),
  m_timestamp(0),
  m_timeSize(0) {
	
}


