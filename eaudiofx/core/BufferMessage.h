/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BUFFER_MESSAGE_H__
#define __EAUDIOFX_BUFFER_MESSAGE_H__

#include <eaudiofx/core/Buffer.h>

namespace eaudiofx {
	enum {
		bufferMessageEndOfStream      = 0x00000001,
		bufferMessageFlush            = 0x00000002,
		bufferMessageReset            = 0x00000004,
		bufferMessageQuery            = 0x00000008,
		bufferMessageQualityOfService = 0x00000010
	};
	class BufferMessage : public eaudiofx::Buffer {
		public:
			BufferMessage(eaudiofx::Block& _parent, int32_t _message = eaudiofx::bufferMessageEndOfStream);
			virtual ~BufferMessage(void) {};
		protected:
			int32_t m_messageId; //!< message ID
		public:
			/**
			 * @brief Get the message.
			 * @return The ID of the message (if value is < 0 : custom message ...)
			 */
			int32_t getMessage(void) {
				return m_messageId;
			}
			/**
			 * @brief Set the message.
			 * @param[in] _message The ID of the message (if value is < 0 : custom message ...)
			 */
			void getMessage(int32_t _messageId) {
				m_messageId = _messageId;
			}
		private:
			std::string m_query;
		public:
			/**
			 * @brief get the query complete message
			 * @return The requested data
			 */
			const std::string& getQuery(void) {
				return m_query;
			}
			/**
			 * @brief get the query complete message
			 * @return The requested data
			 */
			void setQuery(const std::string& _answer) {
				m_query = _answer;
				// reset query:
				if (m_answer.size() != 0) {
					m_answer = "";
				}
			}
		private:
			std::string m_answer;
		public:
			/**
			 * @brief get the answer of the query
			 * @return The requested data
			 */
			const std::string& getAnswer(void) {
				return m_answer;
			}
			/**
			 * @brief get the answer of the query
			 * @return The requested data
			 */
			void setAnswer(const std::string& _answer) {
				m_answer = _answer;
			}
	};
};

#endif


