/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <vector>
#include <map>
#include <ejson/ejson.hpp>

namespace eaudiofx {
	class Block;
	namespace flow {
		class Base;
		class BaseReference;
		class Interface {
			friend class eaudiofx::flow::Base; // to register parameter in the list.
			private:
				std::vector<eaudiofx::flow::Base*> m_list;  //!< list of availlable Flow
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
				void flowAdd(eaudiofx::flow::Base* _pointerOnFlow);
				/**
				 * @brief Un-Register a flow class pointer in the List of flow
				 * @param[in] _pointerOnFlow Pointer on the flow that might be added.
				 */
				void flowRemove(eaudiofx::flow::Base* _pointerOnFlow);
			public:
				/**
				 * @brief Get All the flow list:
				 * @return vector on all the flow names
				 */
				std::vector<std::string> flowGetAll() const;
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
				void flowSetLinkWith(const std::string& _flowName,
				                     const std::string& _blockName,
				                     const std::string& _flowLinkName);
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
				virtual ememory::SharedPtr<eaudiofx::Block> getBlockNamed(const std::string& _name) {
					return nullptr;
				}
				ememory::SharedPtr<eaudiofx::flow::BaseReference> getFlowReference(const std::string& _name);
			public:
				ejson::Object getFlowIntersection(const std::vector<ejson::Object>& _list);
		};
	};
};

