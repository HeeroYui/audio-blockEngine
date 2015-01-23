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
		protected:
			BlockMeta();
			void init() {
				eaudiofx::Block::init();
			}
		public:
			DECLARE_FACTORY(BlockMeta);
			virtual ~BlockMeta();
		private:
			std::vector<std::shared_ptr<eaudiofx::Block>> m_list; //!< list of all block to process.
		protected:
			/**
			 * @brief Get a pointer on a specific block.
			 * @param[in] _name Name of the block.
			 * @return generic error
			 */
			std::shared_ptr<eaudiofx::Block> getBlock(const std::string& _name);
		public:
			/**
			 * @brief Add a block in the Meta-block
			 * @param[in] _block Pointer on the block (do not free yourself)
			 * @return generic error
			 */
			int32_t addBlock(const std::shared_ptr<eaudiofx::Block>& _block);
			/**
			 * @brief Add a block in the Meta-block.
			 * @param[in] _blockType Name of the type of block to add.
			 * @param[in] _name Name of the block to add.
			 * @return generic error
			 */
			int32_t addBlock(const std::string& _blockType, const std::string& _name = "");
			/**
			 * @brief Remove a block from the Meta-block
			 * @param[in] _name Name of the block to remove
			 * @note This free the block pointer
			 * @return generic error
			 */
			int32_t removeBlock(const std::string& _name);
			/**
			 * @brief Link 2 IO.
			 * @param[in] _generatorBlockName Name ot the generator Block
			 * @param[in] _generatorIoName Name of the outout
			 * @param[in] _receiverBlockName Name ot the receiver Block
			 * @param[in] _receiverIoName Name of the input
			 * @return generic error
			 */
			int32_t linkBlock(const std::string& _generatorBlockName,
			                  const std::string& _generatorIoName,
			                  const std::string& _receiverBlockName,
			                  const std::string& _receiverIoName);
			/**
			 * @brief Open file property
			 * @param[in] _fileName Name of the file to open
			 * @return generic error
			 */
			int32_t openFile(const std::string& _fileName);
			/**
			 * @brief Open stream property
			 * @param[in] _stream data stream to open
			 * @return generic error
			 */
			int32_t openStream(const std::string& _stream);
		public: // herited function
			virtual int32_t algoInit();
			virtual int32_t algoUnInit();
			virtual int32_t algoStart();
			virtual int32_t algoStop();
			
			virtual std::shared_ptr<eaudiofx::Block> getBlockNamed(const std::string& _name);
			virtual void flowLinkInput();
			virtual void flowCheckAllCompatibility();
			virtual void flowAllocateOutput();
			virtual void flowGetInput();
	};
};

#endif


