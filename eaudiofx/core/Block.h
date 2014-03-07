/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_H__
#define __EAUDIOFX_BLOCK_H__

#include <eaudiofx/core/audio.h>
#include <string>
#include <mutex>
#include <map>

namespace eaudiofx {
	class Buffer;
	class BlockMeta;
	enum blockType {
		blockTypeUnknow,
		blockTypeFilter,
		blockTypeGenerator,
		blockTypeReceiver,
		blockTypeDecoder,
		blockTypeEncoder,
	};
	class Block {
		public:
			Block(void);
			~Block(void);
		protected:
			std::mutex m_mutex; //!< Block mutex access
		private:
			size_t m_uid; //!< Unique block ID
		public:
			/**
			 * @brief Get the Block Unique ID
			 * @return the UID
			 */
			size_t getUID(void) {
				return m_uid;
			}
		private:
			std::string m_name; //!< name of the block
		public:
			/**
			 * @brief Set the block name
			 * @param[in] _name New name of the Block
			 */
			virtual void setName(const std::string& _name) {
				m_name = _name;
			}
			/**
			 * @brief Set the block name.
			 * @return The block name.
			 */
			virtual const std::string& getName(void) {
				return m_name;
			}
		private:
			enum blockType m_type; // Type of the current block
		public:
			/**
			 * @brief Get block type
			 */
			virtual enum blockType getType(void) {
				return m_type;
			};
		protected:
			/**
			 * @brief Set type of the block ==> detect generator and receiver
			 */
			virtual void setType(enum blockType _type) {
				m_type = _type;
			};
		protected:
			eaudiofx::BlockMeta* m_parent;
		public:
			/**
			 * @brief Get parrent ob this block
			 * @return Pointer on the parrent if one is set.
			 */
			virtual eaudiofx::BlockMeta* getParrent(void) {
				return m_parent;
			};
			/**
			 * @brief Set the parrent pointer.
			 * @param[in] _meta Pointer on the parrent.
			 */
			virtual void setParrent(eaudiofx::BlockMeta* _meta) {
				m_parent = _meta;
			};
		protected:
			// TODO : set properties ...
		public:
			/**
			 * @brief Set a property
			 */
			virtual void setProperty(const std::string& _name, const std::string& _property) {};
			/**
			 * @brief Get a property
			 */
			virtual std::string setProperty(const std::string& _name) {
				return "";
			};
		public:
			/**
			 * @brief Call by downstream to request some data
			 * @param[in] _currentTime Current stream time (in second)
			 * @param[in] _requestTime Data requested (can be chunk number 256 samples, or data byte for stream) (-1 for automatic)
			 * @param[in] _timeout system time to be obsolet (for realTime streaming) (-1 for no realTime streaming)
			 */
			virtual void pull(double _currentTime, int32_t _request, float _timeout) {};
			/**
			 * @brief Get The total stream size (in byte for streaming byte element, in second for time streaming)
			 * @return Get total streaming time (-1 for unknown)
			 */
			virtual double getTotal(void) {
				return -1.0;
			};
			/**
			 * @brief Seek to a specific position in the stream (in byte for streaming byte element, in second for time streaming)
			 * @param[out] _pos position to seek (0 for starting)
			 */
			virtual void seekTo(double _pos) {};
			/**
			 * @brief Request a flush of the current buffer
			 * @param[in] _currentTime Current stream time (in second)
			 * @param[in] _timeout system time to be obsolet (for realTime streaming) (-1 for no realTime streaming)
			 */
			virtual void flush(double _currentTime, float _timeout) {};
			/**
			 * @brief Reset the block
			 */
			virtual void reset(void) {};
		public:
			/**
			 * @brief Call when a buffer is removed from the system (current).
			 * @param[in] _buffer Pointer on the removed buffer.
			 */
			virtual void onRemoveBuffer(const eaudiofx::Buffer* _buffer);
			/**
			 * @brief A child call his parrent that it is removing a buffer.
			 * @param[in] _buffer Pointer on the removed buffer.
			 */
			virtual void subRemoveBuffer(const eaudiofx::Buffer* _buffer);
		protected:
			enum typeIO {
				ioUnknow,
				ioInput,
				ioOutput,
				ioParameter,
			};
			class IOProperty {
				public:
					enum typeIO m_type;
					std::string m_description;
					bool m_internal;
					eaudiofx::Buffer* m_buffer;
					IOProperty(void) :
					  m_type(ioUnknow),
					  m_internal(false),
					  m_buffer(NULL) {
						
					}
			};
			std::map<std::string, eaudiofx::Block::IOProperty> m_io; //!< All IO in the Block
			/**
			 * @brief Link the provided buffer to the IO name.
			 * @param[in] _buffer Pointer on the buffer to link.
			 * @param[in] _name Name of the IO;
			 */
			virtual void linkBuffer(eaudiofx::Buffer* _buffer, const std::string& _name);
			/**
			 * @brief Request a buffer pointer on the IO named.
			 * @param[out] _buffer Pointer on the buffer to link.
			 * @param[in] _name Name of the IO;
			 */
			virtual void getBuffer(eaudiofx::Buffer*& _buffer, const std::string& _name);
			
	};
};

#endif


