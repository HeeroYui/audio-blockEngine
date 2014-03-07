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
  m_time(0) {
	
}