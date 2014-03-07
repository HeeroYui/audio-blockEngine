#!/usr/bin/python
import lutinModule as module
import lutinTools as tools
import lutinDebug as debug

def get_desc():
	return "eaudiofx : Audio interface FX system"


def create(target):
	myModule = module.Module(__file__, 'eaudiofx', 'LIBRARY')
	# System core
	myModule.add_src_file([
		'eaudiofx/debug.cpp',
		'eaudiofx/core/audio.cpp',
		'eaudiofx/core/Processing.cpp',
		'eaudiofx/core/Block.cpp',
		'eaudiofx/core/BlockMeta.cpp',
		'eaudiofx/core/BlockGenerator.cpp',
		'eaudiofx/core/BlockReceiver.cpp',
		'eaudiofx/core/BlockFilter.cpp',
		'eaudiofx/core/BlockDecoder.cpp',
		'eaudiofx/core/BlockEncoder.cpp',
		'eaudiofx/core/Buffer.cpp',
		'eaudiofx/core/BufferMessage.cpp',
		'eaudiofx/core/BufferStream.cpp',
		'eaudiofx/core/BufferAudio.cpp',
		'eaudiofx/core/BufferAudioFreq.cpp',
		'eaudiofx/core/BufferAudioRaw.cpp'
		])
	# basic nodes:
	myModule.add_src_file([
		'eaudiofx/base/GeneratorFile.cpp',
		'eaudiofx/base/ReceiverFile.cpp',
		'eaudiofx/base/GeneratorRtAudio.cpp',
		'eaudiofx/base/ReceiverRtAudio.cpp',
		'eaudiofx/base/GeneratorSignal.cpp'
		])
	
	# name of the dependency
	myModule.add_module_depend(['ewol', 'rtaudio'])
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule









