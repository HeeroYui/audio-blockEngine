/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/flow/Interface.hpp>
#include <audio/blockEngine/flow/Base.hpp>
#include <audio/blockEngine/core/Block.hpp>

audio::blockEngine::flow::Base::Base(audio::blockEngine::flow::Interface& _flowInterfaceLink,
                           bool _input,
                           const etk::String& _name,
                           const etk::String& _description,
                           const etk::String& _formatAvaillable) :
  m_flowInterfaceLink(_flowInterfaceLink),
  m_name(_name),
  m_description(_description),
  m_input(_input) {
	m_ref = ememory::makeShared<BaseReference>(this);
	// add a reference on the current signal ...
	m_flowInterfaceLink.flowAdd(this);
	m_formatAvaillable.parse(_formatAvaillable);
	ABE_INFO("Create flow : '" << m_name << "' mode:'" << (m_input==true?"input":"output") << "' prop:");
	m_formatAvaillable.display();
}

audio::blockEngine::flow::Base::~Base() {
	m_ref->removeBase();
	ABE_INFO("Remove flow : '" << m_name << "' mode:'" << (m_input==true?"input":"output") << "'");
};

etk::Stream& audio::blockEngine::flow::operator <<(etk::Stream& _os, const audio::blockEngine::flow::Base& _obj) {
	_os << _obj.getName();
	return _os;
}

void audio::blockEngine::flow::Base::link() {
	ABE_INFO("    link flow : '" << m_name << "' mode:'" << (m_input==true?"input":"output") << "' (no code)");
}

int32_t audio::blockEngine::flow::Base::checkCompatibility() {
	ABE_INFO("    check flow : '" << m_name << "' (no code)");
	return -1;
}

void audio::blockEngine::flow::Base::getInputBuffer() {
	ABE_INFO("    get Buffers : '" << m_name << "' (no code)");
}

// due to the fact it acces at the block interface, we need to write it here ...
ememory::SharedPtr<audio::blockEngine::flow::BaseReference> audio::blockEngine::flow::Base::getFlowReference(const etk::String& _blockName,
                                                                                         const etk::String& _flowLinkName) {
	ememory::SharedPtr<audio::blockEngine::flow::BaseReference> out;
	if (_flowLinkName == "") {
		ABE_INFO("    Get flow : " << _blockName << ":" << _flowLinkName << " nothing to do ==> no connection ...");
	}
	ememory::SharedPtr<audio::blockEngine::Block> blockRemote = m_flowInterfaceLink.getBlockNamed(_blockName);
	if (blockRemote == nullptr) {
		ABE_ERROR("    Get flow : '" << m_name << "' mode:'input' to " << _blockName << ":" << _flowLinkName << " Error no remote block");
	} else {
		out = blockRemote->getFlowReference(_flowLinkName);
		if (out == nullptr) {
			ABE_ERROR("    Get flow : '" << m_name << "' mode:'input' to " << _blockName << ":" << _flowLinkName << " Error no Flow found");
		} else {
			ABE_INFO("    Get flow : " << _blockName << ":" << _flowLinkName);
		}
	}
	return out;
}

/*
ememory::SharedPtr<audio::blockEngine::Block> audio::blockEngine::flow::Base::getBlockNamed(const etk::String& _name) {
	ABE_ERROR("NEED to call Parrent ...");
	return nullptr;
}
*/
