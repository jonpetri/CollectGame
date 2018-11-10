cmake_minimum_required(VERSION 3.4.3)  # for CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS

MESSAGE(STATUS " ") #Display an empty line
MESSAGE(STATUS "* Shared library")
##
# Sources files path variables declaration
#
    set( sConsoleViewLibraryIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" )
    MESSAGE(STATUS "INCLUDE_DIR: ${sConsoleViewLibraryIncludeDir}")

    set( sConsoleViewLibrarySourceDir "${CMAKE_CURRENT_SOURCE_DIR}" )
    MESSAGE(STATUS "SOURCE_DIR: ${sConsoleViewLibrarySourceDir}")


##
# SOURCE FILES RESEARCH
#
    #Research of .h/.cpp files
	file(GLOB_RECURSE sLibrarySourceFiles  ${sConsoleViewLibraryIncludeDir}/*.h ${sConsoleViewLibrarySourceDir}/*.cpp)
	group_files(sLibrarySourceFiles)
    #target_sources(${sConsoleViewLibraryTargetName} PUBLIC ${sLibrarySourceFiles})  # Doesn't work with Cmake version 3.5.2, which I use for cross compiling (MXE)

##
# TARGET:
#
    Add_library(${sConsoleViewLibraryTargetName} SHARED ${sLibrarySourceFiles})
    MESSAGE(STATUS " ") #Display an empty line

    set_target_properties(${sConsoleViewLibraryTargetName} PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS WIN32
            )


##
# INCLUDES:
#
    target_include_directories(${sConsoleViewLibraryTargetName} PUBLIC ${sConsoleViewLibraryIncludeDir})
    target_include_directories(${sConsoleViewLibraryTargetName} PUBLIC ${sConsoleViewLibrarySourceDir})
	





	
