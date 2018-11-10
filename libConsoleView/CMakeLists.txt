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
    if( "${CMAKE_BUILD_TYPE}" STREQUAL "" )
        set( CMAKE_BUILD_TYPE "Debug" )
    endif()

    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
        Debug Release )

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

    set(Project_Targets_dir ${CMAKE_SOURCE_DIR}/build_targets CACHE STRING "Directory of the output files: exe, dll, so, doc, translations...")
    set(sDebugBuildProductsDir ${Project_Targets_dir}/debug)
    set(sReleaseBuildProductsDir ${Project_Targets_dir}/release)

    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${sDebugBuildProductsDir}/bin" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${sDebugBuildProductsDir}/bin" )
    #set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${sDebugBuildProductsDir}/bin" )

    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${sReleaseBuildProductsDir}/bin" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${sReleaseBuildProductsDir}/bin" )
    #set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${sReleaseBuildProductsDir}/bin" )

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
# boost::signals2  find_package
#
    MESSAGE(STATUS " ") #Display an empty line
    MESSAGE(STATUS "* BOOST REQUIRED for boost::signals2")
    if (WIN32)
        #set(BOOST_ROOT "C:/DEV/TOOLS/Boost/boost")
        #set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
    endif (WIN32)

    #If you run into issues with CMake looking for incorrect library names, this may help:
    #add_definitions(-DBOOST_ALL_NO_LIB)  # tell the compiler to undefine this boost macro
    find_package(Boost REQUIRED)

    message(STATUS "Boost Include: ${Boost_INCLUDE_DIR}")
    message(STATUS "Boost Library dirs: ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")

    # These commands will ensure that Boost libraries (all) are linked dynamically:
    set(Boost_USE_STATIC_LIBS        OFF)
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME     OFF)
    set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries

##
# Sub-directories include
#

    add_subdirectory(src)
    add_subdirectory(test)
