/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/core/BufferMessage.h>



eaudiofx::BufferMessage::BufferMessage(eaudiofx::Block& _parent, int32_t _message) :
  eaudiofx::Buffer(_parent),
  m_messageId(_message) {
	
}
