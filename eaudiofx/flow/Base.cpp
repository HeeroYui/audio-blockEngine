/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <memory>
#include <eaudiofx/debug.h>
#include <eaudiofx/flow/Interface.h>
#include <eaudiofx/flow/Base.h>

eaudiofx::flow::Base::Base(eaudiofx::flow::Interface& _flowInterfaceLink,
                           bool _input,
                           const std::string& _name,
                           const std::string& _description,
                           const std::string& _formatAvaillable) :
  m_flowInterfaceLink(_flowInterfaceLink),
  m_name(_name),
  m_description(_description),
  m_input(_input) {
	// add a reference on the current signal ...
	m_flowInterfaceLink.flowAdd(this);
	m_formatAvaillable.parse(_formatAvaillable);
	EAUDIOFX_INFO(" create flow : " << _name << " mode:'" << (m_input==true?"input":"output") << "' prop:");
	m_formatAvaillable.display();
}

std::ostream& eaudiofx::flow::operator <<(std::ostream& _os, const eaudiofx::flow::Base& _obj) {
	_os << _obj.getName();
	return _os;
}
