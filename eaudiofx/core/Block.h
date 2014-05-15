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
			Block();
			virtual ~Block();
		protected:
			std::mutex m_mutex; //!< Block mutex access
		private:
			size_t m_uid; //!< Unique block ID
		public:
			/**
			 * @brief Get the Block Unique ID
			 * @return the UID
			 */
			size_t getUID() {
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
			virtual const std::string& getName() {
				return m_name;
			}
		private:
			enum blockType m_type; // Type of the current block
		public:
			/**
			 * @brief Get block type
			 */
			virtual enum blockType getType() {
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
			virtual eaudiofx::BlockMeta* getParrent() {
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
			 * @brief Init the block with the properties
			 * @return A generic error.
			 */
			virtual int32_t init() {
				return eaudiofx::ERR_NONE;
			};
			/**
			 * @brief UnInit the block with the properties
			 * @return A generic error.
			 */
			virtual int32_t unInit() {
				return eaudiofx::ERR_NONE;
			};
			virtual int32_t start() {
				return eaudiofx::ERR_NONE;
			};
			virtual int32_t stop() {
				return eaudiofx::ERR_NONE;
			};
			/**
			 * @brief Call by downstream to request some data
			 * @param[in] _currentTime Current stream time (in second)
			 * @param[in] _requestTime Data requested (can be chunk number 256 samples, or data byte for stream) (-1 for automatic)
			 * @param[in] _timeout system time to be obsolet (for realTime streaming) (-1 for no realTime streaming)
			 * @return generic error
			 */
			virtual int32_t pull(double _currentTime, int32_t _request, float _timeout);
			/**
			 * @brief Get The total stream size (in byte for streaming byte element, in second for time streaming)
			 * @param[out] _value Get total streaming time (-1 for unknown)
			 * @return generic error
			 */
			virtual int32_t getTotal(double& _value) {
				_value = -1;
				return eaudiofx::ERR_NONE;
			};
			/**
			 * @brief Seek to a specific position in the stream (in byte for streaming byte element, in second for time streaming)
			 * @param[out] _pos position to seek (0 for starting)
			 * @return generic error
			 */
			virtual int32_t seekTo(double _pos) {
				return eaudiofx::ERR_NONE;
			};
			/**
			 * @brief Request a flush of the current buffer
			 * @param[in] _currentTime Current stream time (in second)
			 * @param[in] _timeout system time to be obsolet (for realTime streaming) (-1 for no realTime streaming)
			 * @return generic error
			 */
			virtual int32_t flush(double _currentTime, float _timeout) {
				return eaudiofx::ERR_NONE;
			};
			/**
			 * @brief Reset the block
			 * @return generic error
			 */
			virtual int32_t reset() {
				return eaudiofx::ERR_NONE;
			};
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
					IOProperty(enum typeIO _type,
					           const std::string& _description="",
					           eaudiofx::Buffer* _buffer = NULL) :
					  m_type(_type),
					  m_description(_description),
					  m_internal(true),
					  m_buffer(_buffer) {
						if (m_type == ioParameter) {
							// TODO : Autogenerate buffer for parameter ...
						}
					}
					IOProperty() :
					  m_type(ioUnknow),
					  m_internal(false),
					  m_buffer(NULL) {
						
					}
			};
			std::map<std::string, eaudiofx::Block::IOProperty> m_io; //!< All IO in the Block
		public:
			/**
			 * @brief Link the provided buffer to the IO name.
			 * @param[in] _buffer Pointer on the buffer to link.
			 * @param[in] _name Name of the IO;
			 * @return A generic error.
			 */
			virtual int32_t linkBuffer(eaudiofx::Buffer* _buffer, const std::string& _name);
			/**
			 * @brief Un link a speific buffer to the IO name.
			 * @param[in] _buffer Pointer on the buffer to unlink.
			 * @param[in] _name Name of the IO to unlink;
			 * @return A generic error.
			 */
			virtual int32_t unLinkBuffer(const eaudiofx::Buffer* _buffer);
			//! @previous
			virtual int32_t unLinkBuffer(const std::string& _name);
			/**
			 * @brief Request a buffer pointer on the IO named.
			 * @param[out] _buffer Pointer on the buffer to link.
			 * @param[in] _name Name of the IO;
			 * @return A generic error.
			 */
			virtual int32_t getBuffer(eaudiofx::Buffer*& _buffer, const std::string& _name);
			/**
			 * @brief Update the IO property
			 * @return A generic error.
			 */
			virtual int32_t UpdateIOProperty() {
				return eaudiofx::ERR_NONE;
			};
	};
};

#endif


