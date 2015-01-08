/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_BLOCK_H__
#define __EAUDIOFX_BLOCK_H__

#include <string>
#include <mutex>
#include <map>
#include <ewol/object/Object.h>
#include <eaudiofx/core/audio.h>
#include <eaudiofx/flow/Interface.h>
#include <eaudiofx/flow/Flow.h>


namespace eaudiofx {
	class Buffer;
	class BlockMeta;
	
	class Block : public ewol::Object,
	              public eaudiofx::flow::Interface {
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


