cmake_minimum_required(VERSION 3.4.3)  # for CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS

##
# PROJECT 
#

    SET(sConsoleViewLibraryTargetName "ConsoleView")
    #SET(sConsoleViewLibraryTargetName ${sConsoleViewLibraryTargetName} PARENT_SCOPE)

    project (${sConsoleViewLibraryTargetName})


    MESSAGE(STATUS " ") #Display an empty line
    MESSAGE("PROJECT: ${sConsoleViewLibraryTargetName}")



##
# Projets's build  type set up: debug or release
#
    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
        Debug Release )

    if( "${CMAKE_BUILD_TYPE}" STREQUAL "" )
        set( CMAKE_BUILD_TYPE "Debug" )
    endif()

    MESSAGE(STATUS "BUILD TYPE: ${CMAKE_BUILD_TYPE}")




##
# Compiler configuration according build type
#
    set(CMAKE_CXX_STANDARD 11)      # setting the language standard, same as add_definitions(-std=c++11)

    if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
      # using GCC

        if( CMAKE_BUILD_TYPE MATCHES Release )
            add_definitions(-O2 -s)
        else ()
            add_definitions(-pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal
            -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion
            -Wshadow -Weffc++ -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default
            -Wswitch-enum -Wundef -Wlogical-op -Winline)
            #add_definitions(-Werror)
        endif()

    #elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      # using Clang
    #elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
      # using Intel C++
    #elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
      # using Visual Studio C++
      #add_definitions(/EHc-)
       ##add_definitions(-DUNICODE -D_UNICODE)
    endif()


##
# PROJECT'S OUTPUT DIRECTORIES
#

    set (Project_Targets_dir ${CMAKE_SOURCE_DIR}/build_targets CACHE STRING "Directory of the output files: exe, dll, so, doc, translations...")
    set(sDebugBuildProductsDir ${Project_Targets_dir}/debug)
    set(sReleaseBuildProductsDir ${Project_Targets_dir}/release)

    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${sDebugBuildProductsDir}" )
    #set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${sDebugBuildProductsDir}/archives" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${sDebugBuildProductsDir}" )

    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${sReleaseBuildProductsDir}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${sReleaseBuildProductsDir}" )
    #set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${sReleaseBuildProductsDir}/archives" )

##
# FUNCTIONS
#
        # groups source files according to the directory structure, usefull for visual studio only
	function(group_files SOURCES)
	  foreach(SOURCE_FILE ${${SOURCES}})
		get_filename_component(GROUP "${SOURCE_FILE}" PATH)
		string(REPLACE "${CMAKE_SOURCE_DIR}" "" GROUP "${GROUP}")
		string(REPLACE "/" "\\" GROUP "${GROUP}")

		set(GROUP "${GROUP}\\")
		foreach(REPL ${ARGN})
		  string(REPLACE "\\${REPL}\\" "\\" GROUP "${GROUP}")
		endforeach()

		source_group("${GROUP}" FILES "${SOURCE_FILE}")
	  endforeach()
	endfunction()



##
# Sub-directories include
#

    add_subdirectory(src)
    add_subdirectory(test)
