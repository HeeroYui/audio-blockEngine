/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0  (see license file)
 */
#pragma once

#include <elog/log.hpp>

namespace audio {
	namespace blockEngine {
		int32_t getLogId();
	}
}
#define ABE_BASE(info,data)  ELOG_BASE(audio::blockEngine::getLogId(),info,data)

#define ABE_PRINT(data)         ABE_BASE(1, data)
#define ABE_CRITICAL(data)      ABE_BASE(1, data)
#define ABE_ERROR(data)         ABE_BASE(2, data)
#define ABE_WARNING(data)       ABE_BASE(3, data)
#ifdef DEBUG
	#define ABE_INFO(data)          ABE_BASE(4, data)
	#define ABE_DEBUG(data)         ABE_BASE(5, data)
	#define ABE_VERBOSE(data)       ABE_BASE(6, data)
	#define ABE_TODO(data)          ABE_BASE(4, "TODO : " << data)
#else
	#define ABE_INFO(data)          do { } while(false)
	#define ABE_DEBUG(data)         do { } while(false)
	#define ABE_VERBOSE(data)       do { } while(false)
	#define ABE_TODO(data)          do { } while(false)
#endif

#define ABE_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			ABE_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)


