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

eaudiofx::flow::Interface::Interface() {
	
}

eaudiofx::flow::Interface::~Interface() {
	m_list.clear();
}

// note this pointer is not allocated and not free at the end of the class
void eaudiofx::flow::Interface::flowAdd(eaudiofx::flow::Base* _pointerOnFlow) {
	if (_pointerOnFlow == nullptr) {
		EAUDIOFX_ERROR("Try to link a nullptr flow");
		return;
	}
	m_list.push_back(_pointerOnFlow);
}

void eaudiofx::flow::Interface::flowRemove(eaudiofx::flow::Base* _pointerOnFlow) {
	if (_pointerOnFlow == nullptr) {
		EAUDIOFX_ERROR("Try to unlink a nullptr flow");
		return;
	}
	for (auto it(m_list.begin()); it != m_list.end(); ++it) {
		if (*it == nullptr) {
			continue;
		}
		if (*it == _pointerOnFlow) {
			m_list.erase(it);
			return;
		}
	}
	EAUDIOFX_ERROR("Try to unlink a Unexistant flow");
}

std::vector<std::string> eaudiofx::flow::Interface::flowGetAll() const {
	std::vector<std::string> out;
	for (auto &it : m_list) {
		if(it != nullptr) {
			out.push_back(it->getName());
		}
	}
	return out;
}

void eaudiofx::flow::Interface::flowRemoveAll() {
	m_list.clear();
}


void eaudiofx::flow::Interface::flowSetLinkWith(const std::string& _flowName,
                                                const std::string& _blockName,
                                                const std::string& _flowLinkName) {
	for (auto &it : m_list) {
		if(    it != nullptr
		    && it->getName() == _flowName) {
			it->setLink(_blockName, _flowLinkName);
			return;
		}
	}
	EAUDIOFX_ERROR("Can not find Flow : '" << _flowName << "'");
}

void eaudiofx::flow::Interface::flowLinkInput() {
	EAUDIOFX_INFO(" Block update the flows links");
	for (auto &it : m_list) {
		if(it != nullptr) {
			it->link();
		}
	}
}

void eaudiofx::flow::Interface::flowCheckAllCompatibility() {
	EAUDIOFX_INFO(" Block Check the flows Capabilities");
	for (auto &it : m_list) {
		if(it != nullptr) {
			it->checkCompatibility();
		}
	}
}

void eaudiofx::flow::Interface::flowAllocateOutput() {
	EAUDIOFX_WARNING(" Block need to allocate all his output");
}

void eaudiofx::flow::Interface::flowGetInput() {
	EAUDIOFX_WARNING(" Block Get input data pointers");
	for (auto &it : m_list) {
		if(it != nullptr) {
			it->getInputBuffer();
		}
	}
}


std::shared_ptr<eaudiofx::flow::BaseReference> eaudiofx::flow::Interface::getFlowReference(const std::string& _flowName) {
	std::shared_ptr<eaudiofx::flow::BaseReference> out;
	for (auto &it : m_list) {
		if(    it != nullptr
		    && it->getName() == _flowName) {
			out = it->getReference();
			break;
		}
	}
	return out;
}


