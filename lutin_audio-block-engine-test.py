#!/usr/bin/python
import lutin.tools as tools
import lutin.debug as debug
import os


def get_type():
	return "BINARY"

def get_name():
	return "audio FX test"

def get_desc():
	return "audio_block_engine_test : Audio interface FX system test example system"

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

def configure(target, my_module):
	# basic GUI :
	my_module.add_src_file([
	    'test/debug.cpp',
	    'test/Main.cpp',
	    'test/Windows.cpp',
	    ])
	
	# name of the dependency
	my_module.add_depend(['ewol', 'audio-block-engine'])
	
	my_module.add_path(".")
	
	my_module.copy_path("data/Font/Free*.ttf","fonts/")
	my_module.copy_path("data/menu*","")
	my_module.set_pkg("SECTION", ["Test"])
	my_module.set_pkg("PRIORITY", "optional")
	return True


