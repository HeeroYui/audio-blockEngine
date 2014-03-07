/**
 * @author Edouard DUPIN
 * 
 * @copyright 2010, Edouard DUPIN, all right reserved
 * 
 * @license BSD 3 clauses (see license file)
 */

#ifndef __APPL_DEBUG_H__
#define __APPL_DEBUG_H__

#include <etk/types.h>
#include <etk/debugGeneric.h>

extern const char * applLogName;

#define APPL_CRITICAL(data)     ETK_CRITICAL(applLogName, data)
#define APPL_WARNING(data)      ETK_WARNING(applLogName, data)
#define APPL_ERROR(data)        ETK_ERROR(applLogName, data)
#define APPL_INFO(data)         ETK_INFO(applLogName, data)
#define APPL_DEBUG(data)        ETK_DEBUG(applLogName, data)
#define APPL_VERBOSE(data)      ETK_VERBOSE(applLogName, data)
#define APPL_ASSERT(cond, data) ETK_ASSERT(applLogName, cond, data)
#define APPL_CHECK_INOUT(cond)  ETK_CHECK_INOUT(applLogName, cond)
#define APPL_TODO(cond)         ETK_TODO(applLogName, cond)


#endif

