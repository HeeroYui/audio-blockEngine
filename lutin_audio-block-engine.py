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
	    'eaudiofx/debug.cpp',
	    'eaudiofx/Thread.cpp',
	    'eaudiofx/flow/Base.cpp',
	    'eaudiofx/flow/Interface.cpp',
	    'eaudiofx/core/audio.cpp',
	    'eaudiofx/core/Processing.cpp',
	    'eaudiofx/core/Block.cpp',
	    'eaudiofx/core/BlockMeta.cpp',
	    'eaudiofx/core/Buffer.cpp',
	    'eaudiofx/core/BufferAudio.cpp',
	    'eaudiofx/core/BufferAudioFreq.cpp'
	    ])
	# basic nodes:
	my_module.add_src_file([
	    #'eaudiofx/base/GeneratorFile.cpp',
	    #'eaudiofx/base/ReceiverFile.cpp',
	    #'eaudiofx/base/GeneratorRiver.cpp',
	    'eaudiofx/base/ReceiverRiver.cpp',
	    'eaudiofx/base/GeneratorSignal.cpp'
	    ])
	
	# name of the dependency
	my_module.add_depend([
	    'audio-river',
	    'ewol',
	    'ejson'
	    ])
	
	my_module.add_path(tools.get_current_path(__file__), export=True)
	return my_module









