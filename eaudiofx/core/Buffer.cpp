/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/core/Buffer.h>



eaudiofx::Buffer::Buffer(eaudiofx::Block& _parent) :
  m_parent(_parent),
  m_timestamp(0),
  m_time(0),
  m_negociated(false) {
	
}


int32_t eaudiofx::Buffer::pull(double _currentTime, int32_t _request, float _timeout) {
	if (_currentTime > m_timestamp) {
		return m_parent.pull(_currentTime, _request, _timeout);
	}
	return eaudiofx::ERR_NONE;
}

