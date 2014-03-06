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
#include <eaudiofx/core/Buffer.h>
#include <string>

namespace eaudiofx {
	class Block {
		public:
			Block(void) {};
			~Block(void) {};
		private:
			std::string m_name; //!< name of the block
		public:
			/**
			 * @brief Set the block name
			 */
			void setName(const std::string& _name) {
				m_name = _name;
			}
			/**
			 * @brief Set the block name
			 */
			const std::string& setName(void) {
				return m_name;
			}
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
			 *
			 */
			virtual int32_t push(int32_t _interface, eaudiofx::Buffer& _buffer, float _timeout) { };
			/**
			 *
			 */
			virtual int32_t pull(int32_t _interface, eaudiofx::Buffer& _buffer, float _timeout) { };
	};
};

#endif


