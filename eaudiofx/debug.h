/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_DEBUG_H__
#define __EAUDIOFX_DEBUG_H__

#include <etk/log.h>

namespace eaudiofx {
	int32_t getLogId();
};
#define EAUDIOFX_BASE(info,data)  TK_LOG_BASE(eaudiofx::getLogId(),info,data)

#define EAUDIOFX_CRITICAL(data)      EAUDIOFX_BASE(1, data)
#define EAUDIOFX_ERROR(data)         EAUDIOFX_BASE(2, data)
#define EAUDIOFX_WARNING(data)       EAUDIOFX_BASE(3, data)
#ifdef DEBUG
	#define EAUDIOFX_INFO(data)          EAUDIOFX_BASE(4, data)
	#define EAUDIOFX_DEBUG(data)         EAUDIOFX_BASE(5, data)
	#define EAUDIOFX_VERBOSE(data)       EAUDIOFX_BASE(6, data)
	#define EAUDIOFX_TODO(data)          EAUDIOFX_BASE(4, "TODO : " << data)
#else
	#define EAUDIOFX_INFO(data)          do { } while(false)
	#define EAUDIOFX_DEBUG(data)         do { } while(false)
	#define EAUDIOFX_VERBOSE(data)       do { } while(false)
	#define EAUDIOFX_TODO(data)          do { } while(false)
#endif

#define EAUDIOFX_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			EAUDIOFX_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

#endif

