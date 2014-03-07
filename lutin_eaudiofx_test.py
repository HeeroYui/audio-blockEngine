#!/usr/bin/python
import lutinModule as module
import lutinTools as tools
import lutinDebug as debug

def get_desc():
	return "eaudiofx_test : Audio interface FX system test example system"


def create(target):
	myModule = module.Module(__file__, 'eaudiofx_test', 'BINARY')
	# basic GUI :
	myModule.add_src_file([
		'test/debug.cpp',
		'test/Main.cpp',
		'test/Windows.cpp',
		])
	
	# name of the dependency
	myModule.add_module_depend(['ewol', 'eaudiofx'])
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule


