/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <eaudiofx/core/BlockGenerator.h>

eaudiofx::BlockGenerator::BlockGenerator(void) :
  m_isLive(false) {
	setType(eaudiofx::blockTypeGenerator);
}

