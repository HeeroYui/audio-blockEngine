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
#include <eaudiofx/core/Block.h>

#undef __class__
#define __class__ "flow::Base"

eaudiofx::flow::Base::Base(eaudiofx::flow::Interface& _flowInterfaceLink,
                           bool _input,
                           const std::string& _name,
                           const std::string& _description,
                           const std::string& _formatAvaillable) :
  m_flowInterfaceLink(_flowInterfaceLink),
  m_name(_name),
  m_description(_description),
  m_input(_input) {
	m_ref = std::make_shared<BaseReference>(this);
	// add a reference on the current signal ...
	m_flowInterfaceLink.flowAdd(this);
	m_formatAvaillable.parse(_formatAvaillable);
	EAUDIOFX_INFO("Create flow : '" << m_name << "' mode:'" << (m_input==true?"input":"output") << "' prop:");
	m_formatAvaillable.display();
}

eaudiofx::flow::Base::~Base() {
	m_ref->removeBase();
	EAUDIOFX_INFO("Remove flow : '" << m_name << "' mode:'" << (m_input==true?"input":"output") << "'");
};

std::ostream& eaudiofx::flow::operator <<(std::ostream& _os, const eaudiofx::flow::Base& _obj) {
	_os << _obj.getName();
	return _os;
}

void eaudiofx::flow::Base::link() {
	EAUDIOFX_INFO("    link flow : '" << m_name << "' mode:'" << (m_input==true?"input":"output") << "' (no code)");
}

void checkCompatibility() {
	EAUDIOFX_INFO("    chack flow : '" << m_name << "' (no code)");
}

void getInputBuffer() {
	EAUDIOFX_INFO("    get Buffers : '" << m_name << "' (no code)");
}

// due to the fact it acces at the block interface, we need to write it here ...
std::shared_ptr<eaudiofx::flow::BaseReference> eaudiofx::flow::Base::getFlowReference(const std::string& _blockName,
                                                                      const std::string& _flowLinkName) {
	std::shared_ptr<eaudiofx::flow::BaseReference> out;
	if (_flowLinkName == "") {
		EAUDIOFX_INFO("    Get flow : " << _blockName << ":" << _flowLinkName << " nothing to do ==> no connection ...");
	}
	std::shared_ptr<eaudiofx::Block> blockRemote = m_flowInterfaceLink.getBlockNamed(_blockName);
	if (blockRemote == nullptr) {
		EAUDIOFX_ERROR("    Get flow : '" << m_name << "' mode:'input' to " << _blockName << ":" << _flowLinkName << " Error no remote block");
	} else {
		out = blockRemote->getFlowReference(_flowLinkName);
		if (out == nullptr) {
			EAUDIOFX_ERROR("    Get flow : '" << m_name << "' mode:'input' to " << _blockName << ":" << _flowLinkName << " Error no Flow found");
		} else {
			EAUDIOFX_INFO("    Get flow : " << _blockName << ":" << _flowLinkName);
		}
	}
	return out;
}

/*
std::shared_ptr<eaudiofx::Block> eaudiofx::flow::Base::getBlockNamed(const std::string& _name) {
	EAUDIOFX_ERROR("NEED to call Parrent ...");
	return nullptr;
}
*/
