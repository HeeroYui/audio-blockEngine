#!/usr/bin/python
import lutinModule as module
import lutinTools as tools
import lutinDebug as debug

def get_desc():
	return "eaudiofx_test : Audio interface FX system test example system"


def create(target):
	myModule = module.Module(__file__, 'eaudiofx_test', 'PACKAGE')
	# basic GUI :
	myModule.add_src_file([
		'test/debug.cpp',
		'test/Main.cpp',
		'test/Windows.cpp',
		])
	
	# name of the dependency
	myModule.add_module_depend(['ewol', 'eaudiofx'])
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	myModule.copy_folder("data/Font/Free*.ttf","fonts/")
	myModule.copy_folder("data/menu*","")
	
	# set the package properties :
	myModule.pkg_set("VERSION", "0.0.0")
	myModule.pkg_set("COMPAGNY_TYPE", "org")
	myModule.pkg_set("COMPAGNY_NAME", "Edouard DUPIN")
	myModule.pkg_set("MAINTAINER", ["Mr DUPIN Edouard <yui.heero@gmail.com>"])
	#if target.name=="MacOs":
	#	myModule.pkg_set("ICON", tools.get_current_path(__file__) + "/../data/icon.icns")
	#else:
	#	myModule.pkg_set("ICON", tools.get_current_path(__file__) + "/../data/icon.png")
	
	myModule.pkg_set("SECTION", ["Test"])
	myModule.pkg_set("PRIORITY", "optional")
	myModule.pkg_set("DESCRIPTION", "Test tool of e-audio-FX")
	myModule.pkg_set("NAME", "e-audio-FX test")
	
	# add the currrent module at the 
	return myModule


