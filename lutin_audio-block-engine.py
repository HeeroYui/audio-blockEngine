#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import lutin.debug as debug
import os

def get_type():
	return "LIBRARY"

def get_name():
	return "audio FX"

def get_desc():
	return "audio_block_engine : Audio interface FX system"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def get_version():
	return "version.txt"


def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	# System core
	my_module.add_src_file([
	    'audio/blockEngine/debug.cpp',
	    'audio/blockEngine/Thread.cpp',
	    'audio/blockEngine/flow/Base.cpp',
	    'audio/blockEngine/flow/Interface.cpp',
	    'audio/blockEngine/core/audio.cpp',
	    'audio/blockEngine/core/Processing.cpp',
	    'audio/blockEngine/core/Block.cpp',
	    'audio/blockEngine/core/BlockMeta.cpp',
	    'audio/blockEngine/core/Buffer.cpp',
	    'audio/blockEngine/core/BufferAudio.cpp',
	    'audio/blockEngine/core/BufferAudioFreq.cpp'
	    ])
	# basic nodes:
	my_module.add_src_file([
	    #'audio/blockEngine/base/GeneratorFile.cpp',
	    #'audio/blockEngine/base/ReceiverFile.cpp',
	    #'audio/blockEngine/base/GeneratorRiver.cpp',
	    'audio//blockEngine/base/ReceiverRiver.cpp',
	    'audio/blockEngine/base/GeneratorSignal.cpp'
	    ])
	
	# name of the dependency
	my_module.add_depend([
	    'audio-river',
	    'ewol',
	    'ejson'
	    ])
	
	my_module.add_header_file([
	    'audio/blockEngine/Thread.hpp',
	    'audio/blockEngine/flow/Base.hpp',
	    'audio/blockEngine/flow/Flow.hpp',
	    'audio/blockEngine/flow/Interface.hpp',
	    'audio/blockEngine/core/Buffer.hpp',
	    'audio/blockEngine/core/BufferAudioFreq.hpp',
	    'audio/blockEngine/core/Block.hpp',
	    'audio/blockEngine/core/BlockMeta.hpp',
	    'audio/blockEngine/core/Processing.hpp',
	    'audio/blockEngine/core/BufferAudio.hpp',
	    'audio/blockEngine/core/audio.hpp',
	    'audio/blockEngine/base/GeneratorRiver.hpp',
	    'audio/blockEngine/base/GeneratorFile.hpp',
	    'audio/blockEngine/base/ReceiverFile.hpp',
	    'audio/blockEngine/base/ReceiverRiver.hpp',
	    'audio/blockEngine/base/GeneratorSignal.hpp',
	    'audio/blockEngine/debug.hpp',
	    'audio/blockEngine/eaudiofx.hpp',
	    ])
	
	#my_module.add_path(tools.get_current_path(__file__))
	
	return my_module









