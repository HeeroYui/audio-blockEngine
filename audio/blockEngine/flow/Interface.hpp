/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <etk/Vector.hpp>
#include <etk/Map.hpp>
#include <ejson/ejson.hpp>

namespace audio {
	namespace blockEngine {
		class Block;
		namespace flow {
			class Base;
			class BaseReference;
			class Interface {
				friend class audio::blockEngine::flow::Base; // to register parameter in the list.
				private:
					etk::Vector<audio::blockEngine::flow::Base*> m_list;  //!< list of availlable Flow
				public:
					/**
					 * @brief Constructor.
					 */
					Interface();
					/**
					 * @brief Destructor.
					 */
					~Interface();
				private:
					/**
					 * @brief Register a flow class pointer in the List of flow
					 * @note This class does not destroy the flow pointer!!!
					 * @param[in] _pointerOnFlow Pointer on the flow that might be added.
					 */
					void flowAdd(audio::blockEngine::flow::Base* _pointerOnFlow);
					/**
					 * @brief Un-Register a flow class pointer in the List of flow
					 * @param[in] _pointerOnFlow Pointer on the flow that might be added.
					 */
					void flowRemove(audio::blockEngine::flow::Base* _pointerOnFlow);
				public:
					/**
					 * @brief Get All the flow list:
					 * @return vector on all the flow names
					 */
					etk::Vector<etk::String> flowGetAll() const;
					/**
					 * @brief Remove all flows.
					 */
					void flowRemoveAll();
					/**
					 * @brief Set the flow link name
					 * @param[in] _flowName Local flow name to link
					 * @param[in] _blockName Extern block name (if "" ==> upper block)
					 * @param[in] _flowLinkName Name of the link
					 */
					void flowSetLinkWith(const etk::String& _flowName,
					                     const etk::String& _blockName,
					                     const etk::String& _flowLinkName);
				public:
					// get pointer on the specidic input and output from all the IOs
					virtual void flowLinkInput();
					// check if the IOs are compatible
					virtual void flowCheckAllCompatibility();
					// Allocate all Outputs
					virtual void flowAllocateOutput();
					// Get pointer on all Inputs
					virtual void flowGetInput();
					
					/**
					 * @brief Get The block named ...
					 * @param[in] _name Name of the block requested
					 * @return The block requested if it exist.
					 */
					virtual ememory::SharedPtr<audio::blockEngine::Block> getBlockNamed(const etk::String& _name) {
						return nullptr;
					}
					ememory::SharedPtr<audio::blockEngine::flow::BaseReference> getFlowReference(const etk::String& _name);
				public:
					ejson::Object getFlowIntersection(const etk::Vector<ejson::Object>& _list);
			};
		}
	}
}

