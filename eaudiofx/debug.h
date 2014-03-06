/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_DEBUG_H__
#define __EAUDIOFX_DEBUG_H__

#include <etk/types.h>
#include <etk/debugGeneric.h>

extern const char * eaudiofxLibName;

#define EAUDIOFX_CRITICAL(data)    ETK_CRITICAL(eaudiofxLibName, data)
#define EAUDIOFX_WARNING(data)     ETK_WARNING(eaudiofxLibName, data)
#define EAUDIOFX_ERROR(data)       ETK_ERROR(eaudiofxLibName, data)
#define EAUDIOFX_INFO(data)        ETK_INFO(eaudiofxLibName, data)
#define EAUDIOFX_DEBUG(data)       ETK_DEBUG(eaudiofxLibName, data)
#define EAUDIOFX_VERBOSE(data)     ETK_VERBOSE(eaudiofxLibName, data)
#define EAUDIOFX_ASSERT(cond,data) ETK_ASSERT(eaudiofxLibName, cond, data)
#define EAUDIOFX_CHECK_INOUT(cond) ETK_CHECK_INOUT(eaudiofxLibName, cond)
#define EAUDIOFX_TODO(cond)        ETK_TODO(eaudiofxLibName, cond)

#endif

