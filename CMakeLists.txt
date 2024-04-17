#
# Copyright (C) Jonathan D. Belanger 2024.
# All Rights Reserved.
#
# This software is furnished under a license and may be used and copied only
# in accordance with the terms of such license and with the inclusion of the
# above copyright notice.  This software or any other copies thereof may not
# be provided or otherwise made available to any other person.  No title to
# and ownership of the software is hereby transferred.
#
# The information in this software is subject to change without notice and
# should not be construed as a commitment by the author or co-authors.
#
# The author and any co-authors assume no responsibility for the use or
# reliability of this software.
#
# Description:
#
#   This the Top-Level CMakeLists.txt file.
#
# Revision History:
#
#   V01.000 16-Apr-2024 Jonathan D. Belanger
#   Initially written.
#
cmake_minimum_required(VERSION 3.29)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Stax-Payment-Queue-Example"
        VERSION "1.0.0"
        DESCRIPTION "Example C++ code for evaluation in regard to potential employment"
        LANGUAGES CXX C)

macro(SearchFiles extension return_list exclusions)
    file(GLOB_RECURSE _files *.${extension})
    foreach(_file ${_files})
        set(excludeFile FALSE)
        foreach(exclusion ${exclusions})
            string(FIND ${_file} ${exclusion} exclusionFound)
            if(NOT exclusionFound EQUAL -1)
                set(excludeFile TRUE)
            endif()
        endforeach()
        if(NOT excludeFile)
            list(APPEND ${return_list} ${_file})
        endif()
    endforeach()
    list(REMOVE_DUPLICATES ${return_list})
endmacro()

macro(SearchDirectories source_files return_list)
    set(dir_list "")
    foreach(source_file ${source_files})
        get_filename_component(dir_path ${source_file} PATH)
        list(APPEND dir_list ${dir_path})
    endforeach()
    list(APPEND ${return_list} ${dir_list})
    list(REMOVE_DUPLICATES ${return_list})
endmacro()

find_package(GTest REQUIRED)
find_package(Git)
find_package(Threads REQUIRED)

include(CheckIncludeFile)

check_include_file("cstdlib" HAVE_CSTDLIB_HXX)
check_include_file("cstddef" HAVE_CSTDDEF_HXX)
check_include_file("pthread.h" HAVE_PTHREAD_H)

list(APPEND exclusions "CMakeFiles")
set(extensions)
list(APPEND extensions "hxx")
set(headerFiles "")
foreach(extension ${extensions})
    SearchFiles(${extension} headerFiles "${exclusions}")
endforeach()

SearchDirectories("${headerFiles}" headerDirs)

foreach(headerDir ${headerDirs})
    include_directories(${headerDir})
endforeach()

enable_testing()

if(GIT_FOUND)
    execute_process(COMMAND
        "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_SHA
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(PACKAGE_GITSHA "\"${GIT_SHA}\"")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Og -ggdb)
else()
    add_compile_options(-O3)
    add_compile_definitions(NDEBUG)
endif()

if(STATIC_COMPILE STREQUAL "yes")
    message(STATUS "Static compilation")
    add_compile_options(-static -lpthread -lrt -Wl,--whole-archive -lpthread -Wl,--no-whole-archive)
    add_link_options(-static)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBS OFF)
endif()

add_subdirectory(test)
