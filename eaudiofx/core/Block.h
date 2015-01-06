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
#include <ewol/object/Object.h>

namespace eaudiofx {
	class Buffer;
	class BlockMeta;
	
	class Block : public ewol::Object {
		protected:
			Block();
			void init() {
				ewol::Object::init();
			}
		public:
			DECLARE_FACTORY(Block);
			virtual ~Block();
		protected:
			std::mutex m_mutex; //!< Block mutex access
		
		
		public:
			/**
			 * @brief Init the block with the properties
			 * @return A generic error.
			 */
			virtual int32_t algoInit() {
				return eaudiofx::ERR_NONE;
			};
			/**
			 * @brief UnInit the block with the properties
			 * @return A generic error.
			 */
			virtual int32_t algoUnInit() {
				return eaudiofx::ERR_NONE;
			};
			virtual int32_t algoStart() {
				return eaudiofx::ERR_NONE;
			};
			virtual int32_t algoStop() {
				return eaudiofx::ERR_NONE;
			};
		public:
			/**
			 * @brief get if the block support the native push interface
			 * @return true if the mode is supported
			 */
			virtual bool supportNativePush() {
				return false;
			}
			/**
			 * @brief get if the block support the native pull interface
			 * @return true if the mode is supported
			 */
			virtual bool supportNativePull() {
				return false;
			}
			/**
			 * @brief get if the block support the native Time interface
			 * @return true if the mode is supported
			 */
			virtual bool supportNativeTime() {
				return false;
			}
		/* *****************************************************************
		   **                            INPUTS                           **
		   ***************************************************************** */
		protected:
			std::vector<std::pair<std::string, std::string>> m_inputCapabilities; //!< Description of the capabilities of all the inputs (name, capacity)
		public:
			int32_t getNumberOfInput() {
				return m_inputCapabilities.size();
			}
			int32_t addInput(const std::string& _name, const std::string& _description) {
				// TODO :Add check of input already exist
				m_inputCapabilities.push_back(std::make_pair(_name,_description));
				return eaudiofx::ERR_NONE;
			}
		protected:
			std::vector<std::string> m_inputLink; //!< Name of output linked
		public:
			void setInputName(size_t _inputId, const std::string& _nameDistantLink);
			void setInputName(const std::string& _nameInput, const std::string& _nameDistantLink);
		protected:
			std::vector<std::shared_ptr<eaudiofx::Buffer>> m_inputs; //!< Link on the input buffer
		public:
			virtual int32_t linkAllInputs() {
				return eaudiofx::ERR_NONE;
			}
			virtual int32_t unLinkAllInputs() {
				return eaudiofx::ERR_NONE;
			}
			
			
			
			
		/* *****************************************************************
		   **                           OUTPUTS                           **
		   ***************************************************************** */
		protected:
			std::vector<std::pair<std::string, std::string>> m_outputCapabilities; //!< Description of the capabilities of all the outputs (name, capacity)
		public:
			int32_t getNumberOfOutput() {
				return m_outputCapabilities.size();
			}
			int32_t addOutput(const std::string& _name, const std::string& _description) {
				// TODO :Add check of output already exist
				m_outputCapabilities.push_back(std::make_pair(_name,_description));
				
				return eaudiofx::ERR_NONE;
			}
		protected:
			std::vector<std::string> m_outputLink; //!< Name of output linked
		public:
			void setOutputName(size_t _inputId, const std::string& _nameDistantLink);
			void setOutputName(const std::string& _nameInput, const std::string& _nameDistantLink);
		protected:
			std::vector<std::shared_ptr<eaudiofx::Buffer>> m_outputs;
		public:
			virtual int32_t allocateAllOutputs(int64_t _processTimeSlot) {
				return eaudiofx::ERR_NONE;
			}
			virtual int32_t cleanAllOutputs() {
				return eaudiofx::ERR_NONE;
			}
		
		
			/**
			 * @brief Reset the block
			 * @return generic error
			 */
			virtual int32_t algoReset() {
				return eaudiofx::ERR_NONE;
			};
			
			int32_t algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
				return eaudiofx::ERR_NONE;
			}
			
	};
};

#endif


