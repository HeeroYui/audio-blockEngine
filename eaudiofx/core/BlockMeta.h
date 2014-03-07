/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_META_H__
#define __EAUDIOFX_BLOCK_META_H__

#include <eaudiofx/core/Block.h>
#include <vector>

namespace eaudiofx {
	class BlockMeta : public eaudiofx::Block {
		public:
			BlockMeta(void);
			~BlockMeta(void);
		private:
			std::vector<eaudiofx::Block*> m_list; //!< list of all block to process.
		public:
			/**
			 * @brief Add a block in the Meta-block
			 * @param[in] _block Pointer on the block (do not free yourself)
			 */
			void addBlock(eaudiofx::Block* _block);
			/**
			 * @brief Add a block in the Meta-block.
			 * @param[in] _blockType Name of the type of block to add.
			 * @param[in] _name Name of the block to add.
			 */
			void addBlock(const std::string& _blockType, const std::string& _name = "");
			/**
			 * @brief Remove a block from the Meta-block
			 * @param[in] _name Name of the block to remove
			 * @note This free the block pointer
			 */
			void removeBlock(const std::string& _name);
			/**
			 * @brief Replace a block with an other
			 * @param[in] _nameUnLink Name of the block to UnLink
			 * @param[in] _nameLink Name of the block to Link
			 * @note This free the block pointer
			 */
			void replaceFilter(const std::string& _nameUnLink, const std::string& _nameLink);
			/**
			 * @brief Link 2 IO.
			 * @param[in] _generatorBlockName Name ot the generator Block
			 * @param[in] _generatorIoName Name of the outout
			 * @param[in] _receiverBlockName Name ot the receiver Block
			 * @param[in] _receiverIoName Name of the input
			 */
			void linkBlock(const std::string& _generatorBlockName,
			               const std::string& _generatorIoName,
			               const std::string& _receiverBlockName,
			               const std::string& _receiverIoName);
			/**
			 * @brief Open file property
			 * @param[in] _fileName Name of the file to open
			 */
			void openFile(const std::string& _fileName);
			/**
			 * @brief Open stream property
			 * @param[in] _stream data stream to open
			 */
			void openStream(const std::string& _stream);
	};
};

#endif


