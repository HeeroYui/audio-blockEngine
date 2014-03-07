/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EAUDIOFX_AUDIO_H__
#define __EAUDIOFX_AUDIO_H__


#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

// defien type : uintXX_t and intXX_t
#ifndef __STDC_LIMIT_MACROS
	#define __STDC_LIMIT_MACROS
#endif
// note in android include the macro of min max are overwitten
#include <stdint.h>

namespace eaudiofx {
	enum channelPosition {
		// From channels
		channelPositionFrontCenter       = 0x10,
		channelPositionFrontLeft         = 0x11,
		channelPositionFrontRight        = 0x12,
		channelPositionFrontTopCenter    = 0x14,
		channelPositionFrontTopLeft      = 0x15,
		channelPositionFrontTopRight     = 0x16,
		channelPositionFrontBottomCenter = 0x18,
		channelPositionFrontBottomLeft   = 0x19,
		channelPositionFrontBottomRight  = 0x1A,
		// Side channels
		channelPositionSideLeft          = 0x21,
		channelPositionSideRight         = 0x22,
		channelPositionSideTopLeft       = 0x25,
		channelPositionSideTopRight      = 0x26,
		channelPositionSideBottomLeft    = 0x29,
		channelPositionSideBottomRight   = 0x2A,
		// Back/rear channels
		channelPositionRearCenter        = 0x40,
		channelPositionRearLeft          = 0x41,
		channelPositionRearRight         = 0x42,
		channelPositionRearTopCenter     = 0x44,
		channelPositionRearTopLeft       = 0x45,
		channelPositionRearTopRight      = 0x56,
		channelPositionRearBottomCenter  = 0x48,
		channelPositionRearBottomLeft    = 0x49,
		channelPositionRearBottomRight   = 0x4A,
		// Other special channels
		channelPositionSubwoofer         = 0x80
	};
	#define MAX_NUMBER_OF_SIMULTANEOUS_CHANNEL (8)
	#define CHANNEL_3D_MASK  0xF0
	#define CHANNEL_3D_FRONT 0x10
	#define CHANNEL_3D_SIDE  0x20
	#define CHANNEL_3D_REAR  0x40
	#define CHANNEL_3D_OTHER 0x80
	
	#define CHANNEL_POS_MASK   0x03
	#define CHANNEL_POS_CENTER 0x00
	#define CHANNEL_POS_LEFT   0x01
	#define CHANNEL_POS_RIGHT  0x02
	
	#define CHANNEL_HEIGHT_MASK   0x0B
	#define CHANNEL_HEIGHT_MEDIUM 0x00
	#define CHANNEL_HEIGHT_TOP    0x04
	#define CHANNEL_HEIGHT_BOTTOM 0x08
	
	namespace exeption {
		class StdExeption: public std::exception {
			private:
				std::string m_comment;
			public:
				StdExeption(const char* _comment) :
				  m_comment(_comment) {
					
				}
				StdExeption(const std::string& _comment) :
				  m_comment(_comment) {
					
				}
				virtual const char* what() const throw() {
					if (m_comment.size() == 0) {
						return "No exeption comment define ...";
					} else {
						return m_comment.c_str();
					}
				};
		};
		extern const StdExeption g_nullInput;
		extern const StdExeption g_blockAlreadyExist;
		extern const StdExeption g_blockHasNoInput;
		extern const StdExeption g_blockHasNoOuput;
		extern const StdExeption g_blockHasNoParameter;
		extern const StdExeption g_forbiden;
	};
};

#endif
