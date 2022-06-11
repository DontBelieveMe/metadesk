cmake_minimum_required(VERSION 3.0)
project(metadesk)

set(src ${CMAKE_CURRENT_LIST_DIR}/source)

add_library(metadesk
	${src}/md.h
	${src}/md_stb_sprintf.h
	${src}/md.c)

target_include_directories(metadesk PUBLIC ${src})

add_library(Metadesk::Metadesk ALIAS metadesk)

