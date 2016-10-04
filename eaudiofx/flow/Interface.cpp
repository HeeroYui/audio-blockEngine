/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <eaudiofx/debug.hpp>
#include <eaudiofx/flow/Interface.hpp>
#include <eaudiofx/flow/Base.hpp>

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
	EAUDIOFX_INFO(" Block update the flows links (" << m_list.size() << " flows)");
	for (auto &it : m_list) {
		if(it != nullptr) {
			it->link();
		}
	}
}

void eaudiofx::flow::Interface::flowCheckAllCompatibility() {
	EAUDIOFX_INFO(" Block Check the flows Capabilities (" << m_list.size() << " flows)");
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


ememory::SharedPtr<eaudiofx::flow::BaseReference> eaudiofx::flow::Interface::getFlowReference(const std::string& _flowName) {
	ememory::SharedPtr<eaudiofx::flow::BaseReference> out;
	for (auto &it : m_list) {
		if(    it != nullptr
		    && it->getName() == _flowName) {
			out = it->getReference();
			break;
		}
	}
	return out;
}

static ejson::Value intersect(const ejson::Value& _obj1, const ejson::Value& _obj2) {
	ejson::Value out;
	if (_obj1.exist() == false) {
		if (_obj2.exist() == false) {
			EAUDIOFX_ERROR("intersect 2 null ptr ...");
			return ejson::Null();
		} else {
			return _obj2.clone();
		}
	}
	if (_obj2.exist() == false) {
		return _obj1.clone();
	}
	if (_obj1.isNull() == true) {
		return _obj2.clone();
	}
	if (_obj1.isNumber() == true) {
		// just a single output value ... just check if it is the same value
		double value = _obj1.toNumber().get();
		if (_obj2.isNumber() == true) {
			if (value == _obj2.toNumber().get()) {
				return ejson::Number(value);
			}
			EAUDIOFX_ERROR("Not the same number value");
		}
		if (_obj2.isArray() == true) {
			const ejson::Array obj = _obj2.toArray();
			for (auto it : obj) {
				if (it.isNumber() == true) {
					if (value == it.toNumber().get()) {
						return ejson::Number(value);
					}
				}
			}
			EAUDIOFX_ERROR("Not the same values ...");
		}
	}
	if (_obj1.isString() == true) {
		// just a single output value ... just check if it is the same value
		std::string value = _obj1.toString().get();
		if (_obj2.isString() == true) {
			if (value == _obj2.toString().get()) {
				return ejson::String(value);
			}
			EAUDIOFX_ERROR("Not the same string value");
		}
		if (_obj2.isArray() == true) {
			const ejson::Array obj = _obj2.toArray();
			for (auto it : obj) {
				if (it.isString() == true) {
					if (value == it.toString().get()) {
						return ejson::String(value);
					}
				}
			}
			EAUDIOFX_ERROR("Not the same values ...");
		}
	}
	if (_obj1.isArray() == true) {
		EAUDIOFX_TODO(" manage array");
	}
	EAUDIOFX_ERROR("Can not intersect elements : (obj1)");
	_obj1.display();
	EAUDIOFX_ERROR("                             (obj2)");
	_obj2.display();
	// remove sublist if it is reduce to 1
	return ejson::Null();
}

ejson::Object eaudiofx::flow::Interface::getFlowIntersection(const std::vector<ejson::Object>& _list) {
	EAUDIOFX_ERROR("-------------- start intersection --------------");
	ejson::Object out;
	if (_list.size() == 0) {
		return out;
	}
	if (_list.size() == 1) {
		out = _list[0].clone().toObject();
		EAUDIOFX_INFO("List clone : ");
		out.display();
		EAUDIOFX_ERROR("-------------- stop intersection (no link ...) --------------");
		return out;
	}
	// check all same type :
	for (int32_t iii=1; iii<_list.size(); ++iii) {
		if (_list[iii].toString().get("type") != _list[0].toString().get("type")) {
			EAUDIOFX_ERROR("All stream have not the same Type ...");
			return out;
		}
	}
	out.add("type", ejson::String(_list[0].toString().get("type")));
	if (out["type"].toString().get() == "audio") {
		// check frequency:
		ejson::Value tmp = ejson::Null();
		for (int32_t iii=0; iii<_list.size(); ++iii) {
			tmp = intersect(tmp, _list[iii]["freq"]);
		}
		out.add("freq", tmp);
		// check format:
		tmp = ejson::Null();
		for (int32_t iii=0; iii<_list.size(); ++iii) {
			tmp = intersect(tmp, _list[iii]["format"]);
		}
		out.add("format", tmp);
		
		// check channels:
		tmp = ejson::Null();
		for (int32_t iii=0; iii<_list.size(); ++iii) {
			tmp = intersect(tmp, _list[iii]["channels"]);
		}
		out.add("channels", tmp);
		
	} else if (out["type"].toString().get() == "video") {
		for (int32_t iii=1; iii<_list.size(); ++iii) {
			
		}
	} else {
		EAUDIOFX_ERROR("not manage interface for mix ... '" << out["type"].toString().get() << "'");
	}
	out.display();
	EAUDIOFX_ERROR("-------------- stop intersection --------------");
	return out;
}



