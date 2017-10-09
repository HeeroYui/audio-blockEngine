/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <etk/String.hpp>
#include <ethread/Mutex.hpp>
#include <etk/Map.hpp>
#include <ewol/object/Object.hpp>
#include <audio/blockEngine/core/audio.hpp>
#include <audio/blockEngine/flow/Interface.hpp>
#include <audio/blockEngine/flow/Flow.hpp>


namespace audio {
	namespace blockEngine {
		class Buffer;
		class BlockMeta;
		
		class Block : public ewol::Object,
		              public audio::blockEngine::flow::Interface {
			protected:
				Block();
				void init() {
					ewol::Object::init();
				}
			public:
				DECLARE_FACTORY(Block);
				virtual ~Block();
			protected:
				ethread::Mutex m_mutex; //!< Block mutex access
			
			
			public:
				/**
				 * @brief Init the block with the properties
				 * @return A generic error.
				 */
				virtual int32_t algoInit() {
					return audio::blockEngine::ERR_NONE;
				};
				/**
				 * @brief UnInit the block with the properties
				 * @return A generic error.
				 */
				virtual int32_t algoUnInit() {
					return audio::blockEngine::ERR_NONE;
				};
				virtual int32_t algoStart() {
					return audio::blockEngine::ERR_NONE;
				};
				virtual int32_t algoStop() {
					return audio::blockEngine::ERR_NONE;
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
					return audio::blockEngine::ERR_NONE;
				};
				
				int32_t algoProcess(int64_t _currentTime, int64_t _processTimeSlot) {
					return audio::blockEngine::ERR_NONE;
				}
				virtual ememory::SharedPtr<audio::blockEngine::Block> getBlockNamed(const etk::String& _name);
		};
	}
}



