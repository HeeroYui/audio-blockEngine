/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <etk/Function.hpp>
#include <audio/blockEngine/flow/Base.hpp>
#include <audio/blockEngine/core/Buffer.hpp>
#include <audio/blockEngine/debug.hpp>

namespace audio {
	namespace blockEngine {
		class Buffer;
		template<typename T = audio::blockEngine::Buffer> class Flow : public flow::Base {
			protected:
				ememory::SharedPtr<audio::blockEngine::Buffer> m_data;
			public:
				/**
				 * @brief Create a parameter with a specific type.
				 * @param[in] _flowInterfaceLink reference on the parameter lister.
				 * @param[in] _input Select input or output.
				 * @param[in] _name Static name of the flow.
				 * @param[in] _description description of the flow.
				 * @param[in] _formatAvaillable List of format availlable (or {} of all)
				 */
				Flow(audio::blockEngine::flow::Interface& _flowInterfaceLink,
				     bool _input,
				     const etk::String& _name,
				     const etk::String& _description = "",
				     const etk::String& _formatAvaillable="{}") :
				  flow::Base(_flowInterfaceLink, _input, _name, _description, _formatAvaillable) {
					
				};
				/**
				 * @brief Destructor.
				 */
				virtual ~Flow() { };
				void set(const ememory::SharedPtr<audio::blockEngine::Buffer>& _data){
					m_data.reset();
					ememory::SharedPtr<T> check = ememory::dynamicPointerCast<T>(_data);
					if (check == nullptr) {
						ABE_ERROR("can not set buffer as flow (type uncompatible)");
						return;
					}
					m_data = _data;
				}
				T* get() {
					return static_cast<T*>(*m_data);
				}
		};
		namespace flow {
			template<typename T> class Input : public Flow<T> {
				private:
					etk::String m_blockName; //!< Temporary value of flow link (when not linked & distant block can be created after) : Block name
					etk::String m_flowName; //!< Temporary value of flow link (when not linked & distant block can be created after) : Flow name
					ememory::WeakPtr<BaseReference> m_remoteFlow; //!< reference on the remote flow.
				public:
					/**
					 * @brief Create a parameter with a specific type.
					 * @param[in] _flowInterfaceLink reference on the parameter lister.
					 * @param[in] _name Static name of the flow.
					 * @param[in] _description description of the flow.
					 * @param[in] _formatAvaillable List of format availlable (or {} of all)
					 */
					Input(audio::blockEngine::flow::Interface& _flowInterfaceLink,
					      const etk::String& _name,
					      const etk::String& _description = "",
					      const etk::String& _formatAvaillable="{}") :
					  Flow<T>(_flowInterfaceLink, true, _name, _description, _formatAvaillable) {
						
					};
					/**
					 * @brief Destructor.
					 */
					virtual ~Input() { };
					virtual void setLink(const etk::String& _blockName,
					                     const etk::String& _flowLinkName) {
						m_blockName = _blockName;
						m_flowName = _flowLinkName;
						ABE_INFO("[" << Base::m_name << "] Link with : '" << m_blockName << "':'" << m_flowName << "'");
					}
					virtual void link() {
						ABE_INFO("    link flow : '" << Base::m_name << "' mode:'input' to " << m_blockName << ":" << m_flowName);
						ememory::SharedPtr<BaseReference> remoteFlow = Base::getFlowReference(m_blockName, m_flowName);
						m_remoteFlow = remoteFlow;
						if (remoteFlow == nullptr) {
							ABE_ERROR("    link flow : '" << Base::m_name << "' mode:'input' to " << m_blockName << ":" << m_flowName << " Error no Flow found");
							return;
						}
						// set our own cross reference to the remote ...
						remoteFlow->getBase()->addReference(Base::getReference());
					}
			};
			template<typename T> class Output : public Flow<T> {
				protected:
					etk::Vector<ememory::WeakPtr<BaseReference>> m_remoteFlow; //!< List of reference on the remote flow (multiple childs).
					ejson::Object m_formatMix; //!< current format that is now availlable on the flow (can be on error) represent the intersection of all flow connected
				public:
					/**
					 * @brief Create a parameter with a specific type.
					 * @param[in] _flowInterfaceLink reference on the parameter lister.
					 * @param[in] _name Static name of the flow.
					 * @param[in] _description description of the flow.
					 * @param[in] _formatAvaillable List of format availlable (or {} of all)
					 */
					Output(audio::blockEngine::flow::Interface& _flowInterfaceLink,
					       const etk::String& _name,
					       const etk::String& _description = "",
					       const etk::String& _formatAvaillable="{}") :
					  Flow<T>(_flowInterfaceLink, false, _name, _description, _formatAvaillable) {
						
					};
					/**
					 * @brief Destructor.
					 */
					virtual ~Output() { };
					virtual void addReference(const ememory::SharedPtr<BaseReference>& _reference) {
						m_remoteFlow.pushBack(_reference);
					}
					virtual int32_t checkCompatibility() {
						ABE_INFO("        check for : '" << Base::m_name << "' to " << m_remoteFlow.size() << " links");
						etk::Vector<ejson::Object> list;
						list.pushBack(Base::getCapabilities());
						for (auto &it : m_remoteFlow) {
							ememory::SharedPtr<BaseReference> tmp = it.lock();
							if (tmp != nullptr) {
								if (tmp->getBase() != nullptr) {
									list.pushBack(tmp->getBase()->getCapabilities());
								}
							}
						}
						m_formatMix = Base::m_flowInterfaceLink.getFlowIntersection(list);
						
						// TODO : Check input property
						ABE_INFO("[" << Base::m_name << "] mix signal : ");
						m_formatMix.display();
						return 0;
					}
					
			};
		}
	}
}

