/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <ejson/ejson.hpp>
#include <audio/blockEngine/flow/Interface.hpp>
#include <audio/blockEngine/debug.hpp>
#include <ememory/memory.hpp>


namespace audio {
		namespace blockEngine {
		namespace flow {
			class BaseReference;
			class Base {
				protected:
					audio::blockEngine::flow::Interface& m_flowInterfaceLink;
					std::string m_name;
					std::string m_description;
					bool m_input;
					ejson::Document m_formatAvaillable;
				public:
					/**
					 * @brief Create a parameter with a specific type.
					 * @param[in] _flowInterfaceLink reference on the flow list.
					 * @param[in] _input Select input or output.
					 * @param[in] _name Static name of the parameter.
					 * @param[in] _description description of the parameter.
					 * @param[in] _formatAvaillable List of format availlable (or {} of all)
					 */
					Base(audio::blockEngine::flow::Interface& _flowInterfaceLink,
					     bool _input,
					     const std::string& _name,
					     const std::string& _description = "",
					     const std::string& _formatAvaillable="{}");
					/**
					 * @brief Destructor.
					 */
					virtual ~Base();
					
					const std::string& getName() const {
						return m_name;
					}
					const std::string& getDescription() const {
						return m_description;
					}
					bool isInput() {
						return m_input;
					}
					bool isOutput() {
						return !m_input;
					}
					const ejson::Object getCapabilities() {
						return m_formatAvaillable;
					}
					/**
					 * @brief Set the flow link name
					 * @param[in] _blockName Extern block name (if "" ==> upper block)
					 * @param[in] _flowLinkName Name of the link
					 */
					virtual void setLink(const std::string& _blockName,
					                     const std::string& _flowLinkName) {
						ABE_ERROR("[" << m_name << "] Can not create a link on an Output (only manage with input ...)");
					}
				protected:
					ememory::SharedPtr<BaseReference> m_ref; //!< To simplify implementation code we use a temporary variable to shared the current reference...
				public:
					ememory::SharedPtr<BaseReference> getReference() {
						return m_ref;
					}
					virtual void addReference(const ememory::SharedPtr<BaseReference>& _reference) {
						ABE_ERROR("[" << m_name << "] Can not add reference ...");
					}
				protected:
					ememory::SharedPtr<BaseReference> getFlowReference(const std::string& _blockName,
					                                                   const std::string& _flowLinkName);
				public:
					virtual void link();
					virtual int32_t checkCompatibility();
					virtual void getInputBuffer();
					//virtual ememory::SharedPtr<audio::blockEngine::Block> getBlockNamed(const std::string& _name);
			};
			std::ostream& operator <<(std::ostream& _os, const audio::blockEngine::flow::Base& _obj);
			// we use a reference to simplify code of every blocks...
			//! @not-in-doc
			class BaseReference : public ememory::EnableSharedFromThis<BaseReference> {
				protected:
					Base* m_basePointer;
				public:
					BaseReference(Base* _base = nullptr) :
					  m_basePointer(_base) {
						// nothing to do ...
					}
					~BaseReference() {}
					void removeBase() {
						m_basePointer = nullptr;
					}
					inline Base* getBase() const {
						return m_basePointer;
					}
			};
		}
	}
}

