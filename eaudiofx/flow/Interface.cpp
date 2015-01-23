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

static std::shared_ptr<ejson::Value> intersect(const std::shared_ptr<const ejson::Value>& _obj1, const std::shared_ptr<const ejson::Value>& _obj2) {
	std::shared_ptr<ejson::Value> out = ejson::Object::create();
	
	if (_obj1 == nullptr) {
		if (_obj2 == nullptr) {
			EAUDIOFX_ERROR("intersect 2 null ptr ...");
			return ejson::Null::create();
		} else {
			return _obj2->clone();
		}
	}
	if (_obj2 == nullptr) {
		return _obj1->clone();
	}
	if (_obj1->isNull() == true) {
		return _obj2->clone();
	}
	if (_obj1->isNumber() == true) {
		// just a single output value ... just check if it is the same value
		double value = _obj1->toNumber()->get();
		if (_obj2->isNumber() == true) {
			if (value == _obj2->toNumber()->get()) {
				return ejson::Number::create(value);
			}
			EAUDIOFX_ERROR("Not the same number value");
		}
		if (_obj2->isArray() == true) {
			std::shared_ptr<const ejson::Array> obj = _obj2->toArray();
			for (int32_t iii=0; iii<obj->size(); ++iii) {
				if ((*obj)[iii]->isNumber() == true) {
					if (value == (*obj)[iii]->toNumber()->get()) {
						return ejson::Number::create(value);
					}
				}
			}
			EAUDIOFX_ERROR("Not the same values ...");
		}
	}
	if (_obj1->isString() == true) {
		// just a single output value ... just check if it is the same value
		std::string value = _obj1->toString()->get();
		if (_obj2->isString() == true) {
			if (value == _obj2->toString()->get()) {
				return ejson::String::create(value);
			}
			EAUDIOFX_ERROR("Not the same string value");
		}
		if (_obj2->isArray() == true) {
			std::shared_ptr<const ejson::Array> obj = _obj2->toArray();
			for (int32_t iii=0; iii<obj->size(); ++iii) {
				if ((*obj)[iii]->isString() == true) {
					if (value == (*obj)[iii]->toString()->get()) {
						return ejson::String::create(value);
					}
				}
			}
			EAUDIOFX_ERROR("Not the same values ...");
		}
	}
	if (_obj1->isArray() == true) {
		EAUDIOFX_TODO(" manage array");
	}
	EAUDIOFX_ERROR("Can not intersect elements : (obj1)");
	_obj1->display();
	EAUDIOFX_ERROR("                             (obj2)");
	_obj2->display();
	// remove sublist if it is reduce to 1
	return ejson::Null::create();
}

std::shared_ptr<ejson::Document> eaudiofx::flow::Interface::getFlowIntersection(const std::vector<std::shared_ptr<const ejson::Object>>& _list) {
	EAUDIOFX_ERROR("-------------- start intersection --------------");
	std::shared_ptr<ejson::Document> out = std::make_shared<ejson::Document>();
	if (_list.size() == 0) {
		return out;
	}
	if (_list.size() == 1) {
		_list[0]->cloneIn(out);
		EAUDIOFX_INFO("List clone : ");
		out->display();
		EAUDIOFX_ERROR("-------------- stop intersection (no link ...) --------------");
		return out;
	}
	// check all same type :
	for (int32_t iii=1; iii<_list.size(); ++iii) {
		if (_list[iii]->getStringValue("type") != _list[0]->getStringValue("type")) {
			EAUDIOFX_ERROR("All stream have not the same Type ...");
			return out;
		}
	}
	out->add("type", ejson::String::create(_list[0]->getStringValue("type")));
	if (out->getStringValue("type") == "audio") {
		// check frequency:
		std::shared_ptr<ejson::Value> tmp = ejson::Null::create();
		for (int32_t iii=0; iii<_list.size(); ++iii) {
			tmp = intersect(tmp, _list[iii]->get("freq"));
		}
		out->add("freq", tmp);
		// check format:
		tmp = ejson::Null::create();
		for (int32_t iii=0; iii<_list.size(); ++iii) {
			tmp = intersect(tmp, _list[iii]->get("format"));
		}
		out->add("format", tmp);
		
		// check channels:
		tmp = ejson::Null::create();
		for (int32_t iii=0; iii<_list.size(); ++iii) {
			tmp = intersect(tmp, _list[iii]->get("channels"));
		}
		out->add("channels", tmp);
		
	} else if (out->getStringValue("type") == "video") {
		for (int32_t iii=1; iii<_list.size(); ++iii) {
			
		}
	} else {
		EAUDIOFX_ERROR("not manage interface for mix ... '" << out->getStringValue("type") << "'");
	}
	out->display();
	EAUDIOFX_ERROR("-------------- stop intersection --------------");
	return out;
}



