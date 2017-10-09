/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */

#include <audio/blockEngine/debug.hpp>
#include <audio/blockEngine/flow/Interface.hpp>
#include <audio/blockEngine/flow/Base.hpp>

audio::blockEngine::flow::Interface::Interface() {
	
}

audio::blockEngine::flow::Interface::~Interface() {
	m_list.clear();
}

// note this pointer is not allocated and not free at the end of the class
void audio::blockEngine::flow::Interface::flowAdd(audio::blockEngine::flow::Base* _pointerOnFlow) {
	if (_pointerOnFlow == nullptr) {
		ABE_ERROR("Try to link a nullptr flow");
		return;
	}
	m_list.pushBack(_pointerOnFlow);
}

void audio::blockEngine::flow::Interface::flowRemove(audio::blockEngine::flow::Base* _pointerOnFlow) {
	if (_pointerOnFlow == nullptr) {
		ABE_ERROR("Try to unlink a nullptr flow");
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
	ABE_ERROR("Try to unlink a Unexistant flow");
}

etk::Vector<etk::String> audio::blockEngine::flow::Interface::flowGetAll() const {
	etk::Vector<etk::String> out;
	for (auto &it : m_list) {
		if(it != nullptr) {
			out.pushBack(it->getName());
		}
	}
	return out;
}

void audio::blockEngine::flow::Interface::flowRemoveAll() {
	m_list.clear();
}


void audio::blockEngine::flow::Interface::flowSetLinkWith(const etk::String& _flowName,
                                                const etk::String& _blockName,
                                                const etk::String& _flowLinkName) {
	for (auto &it : m_list) {
		if(    it != nullptr
		    && it->getName() == _flowName) {
			it->setLink(_blockName, _flowLinkName);
			return;
		}
	}
	ABE_ERROR("Can not find Flow : '" << _flowName << "'");
}

void audio::blockEngine::flow::Interface::flowLinkInput() {
	ABE_INFO(" Block update the flows links (" << m_list.size() << " flows)");
	for (auto &it : m_list) {
		if(it != nullptr) {
			it->link();
		}
	}
}

void audio::blockEngine::flow::Interface::flowCheckAllCompatibility() {
	ABE_INFO(" Block Check the flows Capabilities (" << m_list.size() << " flows)");
	for (auto &it : m_list) {
		if(it != nullptr) {
			it->checkCompatibility();
		}
	}
}

void audio::blockEngine::flow::Interface::flowAllocateOutput() {
	ABE_WARNING(" Block need to allocate all his output");
}

void audio::blockEngine::flow::Interface::flowGetInput() {
	ABE_WARNING(" Block Get input data pointers");
	for (auto &it : m_list) {
		if(it != nullptr) {
			it->getInputBuffer();
		}
	}
}


ememory::SharedPtr<audio::blockEngine::flow::BaseReference> audio::blockEngine::flow::Interface::getFlowReference(const etk::String& _flowName) {
	ememory::SharedPtr<audio::blockEngine::flow::BaseReference> out;
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
			ABE_ERROR("intersect 2 null ptr ...");
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
			ABE_ERROR("Not the same number value");
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
			ABE_ERROR("Not the same values ...");
		}
	}
	if (_obj1.isString() == true) {
		// just a single output value ... just check if it is the same value
		etk::String value = _obj1.toString().get();
		if (_obj2.isString() == true) {
			if (value == _obj2.toString().get()) {
				return ejson::String(value);
			}
			ABE_ERROR("Not the same string value");
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
			ABE_ERROR("Not the same values ...");
		}
	}
	if (_obj1.isArray() == true) {
		ABE_TODO(" manage array");
	}
	ABE_ERROR("Can not intersect elements : (obj1)");
	_obj1.display();
	ABE_ERROR("                             (obj2)");
	_obj2.display();
	// remove sublist if it is reduce to 1
	return ejson::Null();
}

ejson::Object audio::blockEngine::flow::Interface::getFlowIntersection(const etk::Vector<ejson::Object>& _list) {
	ABE_ERROR("-------------- start intersection --------------");
	ejson::Object out;
	if (_list.size() == 0) {
		return out;
	}
	if (_list.size() == 1) {
		out = _list[0].clone().toObject();
		ABE_INFO("List clone : ");
		out.display();
		ABE_ERROR("-------------- stop intersection (no link ...) --------------");
		return out;
	}
	// check all same type :
	for (int32_t iii=1; iii<_list.size(); ++iii) {
		if (_list[iii].toString().get("type") != _list[0].toString().get("type")) {
			ABE_ERROR("All stream have not the same Type ...");
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
		ABE_ERROR("not manage interface for mix ... '" << out["type"].toString().get() << "'");
	}
	out.display();
	ABE_ERROR("-------------- stop intersection --------------");
	return out;
}



