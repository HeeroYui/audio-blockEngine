/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __EAUDIOFX_FLOW_H__
#define __EAUDIOFX_FLOW_H__

#include <functional>
#include <eaudiofx/flow/Base.h>
#include <eaudiofx/core/Buffer.h>
#include <eaudiofx/debug.h>

namespace eaudiofx {
	class Buffer;
	#undef __class__
	#define __class__ "Flow<T>"
	template<typename T = eaudiofx::Buffer> class Flow : public flow::Base {
		protected:
			std::shared_ptr<eaudiofx::Buffer> m_data;
		public:
			/**
			 * @brief Create a parameter with a specific type.
			 * @param[in] _flowInterfaceLink reference on the parameter lister.
			 * @param[in] _input Select input or output.
			 * @param[in] _name Static name of the flow.
			 * @param[in] _description description of the flow.
			 * @param[in] _formatAvaillable List of format availlable (or {} of all)
			 */
			Flow(eaudiofx::flow::Interface& _flowInterfaceLink,
			     bool _input,
			     const std::string& _name,
			     const std::string& _description = "",
			     const std::string& _formatAvaillable="{}") :
			  flow::Base(_flowInterfaceLink, _input, _name, _description, _formatAvaillable) {
				
			};
			/**
			 * @brief Destructor.
			 */
			virtual ~Flow() { };
			void set(const std::shared_ptr<eaudiofx::Buffer>& _data){
				m_data.reset();
				std::shared_ptr<T> check = std::dynamic_pointer_cast<T>(_data);
				if (check == nullptr) {
					EAUDIOFX_ERROR("can not set buffer as flow (type uncompatible)");
					return;
				}
				m_data = _data;
			}
			T* get() {
				return static_cast<T*>(*m_data);
			}
	};
	namespace flow {
		#undef __class__
		#define __class__ "flow::Input"
		template<typename T> class Input : public Flow<T> {
			private:
				std::string m_blockName; //!< Temporary value of flow link (when not linked & distant block can be created after) : Block name
				std::string m_flowName; //!< Temporary value of flow link (when not linked & distant block can be created after) : Flow name
			public:
				/**
				 * @brief Create a parameter with a specific type.
				 * @param[in] _flowInterfaceLink reference on the parameter lister.
				 * @param[in] _name Static name of the flow.
				 * @param[in] _description description of the flow.
				 * @param[in] _formatAvaillable List of format availlable (or {} of all)
				 */
				Input(eaudiofx::flow::Interface& _flowInterfaceLink,
				      const std::string& _name,
				      const std::string& _description = "",
				      const std::string& _formatAvaillable="{}") :
				  Flow<T>(_flowInterfaceLink, true, _name, _description, _formatAvaillable) {
					
				};
				/**
				 * @brief Destructor.
				 */
				virtual ~Input() { };
				virtual void setLink(const std::string& _blockName,
				                     const std::string& _flowLinkName) {
					m_blockName = _blockName;
					m_flowName = _flowLinkName;
					EAUDIOFX_INFO("[" << Base::m_name << "] Link with : '" << m_blockName << "':'" << m_flowName << "'");
				}
		};
		#undef __class__
		#define __class__ "flow::Output"
		template<typename T> class Output : public Flow<T> {
			public:
				/**
				 * @brief Create a parameter with a specific type.
				 * @param[in] _flowInterfaceLink reference on the parameter lister.
				 * @param[in] _name Static name of the flow.
				 * @param[in] _description description of the flow.
				 * @param[in] _formatAvaillable List of format availlable (or {} of all)
				 */
				Output(eaudiofx::flow::Interface& _flowInterfaceLink,
				       const std::string& _name,
				       const std::string& _description = "",
				      const std::string& _formatAvaillable="{}") :
				  Flow<T>(_flowInterfaceLink, false, _name, _description, _formatAvaillable) {
					
				};
				/**
				 * @brief Destructor.
				 */
				virtual ~Output() { };
		};
	};
	#undef __class__
	#define __class__ nullptr
};
#endif
