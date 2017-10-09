/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <audio/blockEngine/core/Block.hpp>
#include <etk/Vector.hpp>

namespace audio {
	namespace blockEngine {
		class BlockMeta : public audio::blockEngine::Block {
			protected:
				BlockMeta();
				void init() {
					audio::blockEngine::Block::init();
				}
			public:
				DECLARE_FACTORY(BlockMeta);
				virtual ~BlockMeta();
			private:
				etk::Vector<ememory::SharedPtr<audio::blockEngine::Block>> m_list; //!< list of all block to process.
			protected:
				/**
				 * @brief Get a pointer on a specific block.
				 * @param[in] _name Name of the block.
				 * @return generic error
				 */
				ememory::SharedPtr<audio::blockEngine::Block> getBlock(const etk::String& _name);
			public:
				/**
				 * @brief Add a block in the Meta-block
				 * @param[in] _block Pointer on the block (do not free yourself)
				 * @return generic error
				 */
				int32_t addBlock(ememory::SharedPtr<audio::blockEngine::Block> _block);
				/**
				 * @brief Add a block in the Meta-block.
				 * @param[in] _blockType Name of the type of block to add.
				 * @param[in] _name Name of the block to add.
				 * @return generic error
				 */
				int32_t addBlock(const etk::String& _blockType, const etk::String& _name = "");
				/**
				 * @brief Remove a block from the Meta-block
				 * @param[in] _name Name of the block to remove
				 * @note This free the block pointer
				 * @return generic error
				 */
				int32_t removeBlock(const etk::String& _name);
				/**
				 * @brief Link 2 IO.
				 * @param[in] _generatorBlockName Name ot the generator Block
				 * @param[in] _generatorIoName Name of the outout
				 * @param[in] _receiverBlockName Name ot the receiver Block
				 * @param[in] _receiverIoName Name of the input
				 * @return generic error
				 */
				int32_t linkBlock(const etk::String& _generatorBlockName,
				                  const etk::String& _generatorIoName,
				                  const etk::String& _receiverBlockName,
				                  const etk::String& _receiverIoName);
				/**
				 * @brief Open file property
				 * @param[in] _fileName Name of the file to open
				 * @return generic error
				 */
				int32_t openFile(const etk::String& _fileName);
				/**
				 * @brief Open stream property
				 * @param[in] _stream data stream to open
				 * @return generic error
				 */
				int32_t openStream(const etk::String& _stream);
			public: // herited function
				virtual int32_t algoInit();
				virtual int32_t algoUnInit();
				virtual int32_t algoStart();
				virtual int32_t algoStop();
				
				virtual ememory::SharedPtr<audio::blockEngine::Block> getBlockNamed(const etk::String& _name);
				virtual void flowLinkInput();
				virtual void flowCheckAllCompatibility();
				virtual void flowAllocateOutput();
				virtual void flowGetInput();
		};
	}
}



