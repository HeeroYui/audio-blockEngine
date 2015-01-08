/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __EAUDIOFX_FLOW_BASE_H__
#define __EAUDIOFX_FLOW_BASE_H__

#include <ejson/ejson.h>
#include <eaudiofx/flow/Interface.h>
#include <eaudiofx/debug.h>



namespace eaudiofx {
	namespace flow {
		class Base {
			protected:
				eaudiofx::flow::Interface& m_flowInterfaceLink;
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
				Base(eaudiofx::flow::Interface& _flowInterfaceLink,
				     bool _input,
				     const std::string& _name,
				     const std::string& _description = "",
				     const std::string& _formatAvaillable="{}");
				/**
				 * @brief Destructor.
				 */
				virtual ~Base() { };
				
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
				const ejson::Object& getCapabilities() {
					return m_formatAvaillable;
				}
				/**
				 * @brief Set the flow link name
				 * @param[in] _blockName Extern block name (if "" ==> upper block)
				 * @param[in] _flowLinkName Name of the link
				 */
				virtual void setLink(const std::string& _blockName,
				                     const std::string& _flowLinkName) {
					EAUDIOFX_ERROR("[" << m_name << "] Can not create a link on an Output (only manage with input ...)");
				}
		};
		std::ostream& operator <<(std::ostream& _os, const eaudiofx::flow::Base& _obj);
	};
};
#endif
