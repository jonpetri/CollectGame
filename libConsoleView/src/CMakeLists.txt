cmake_minimum_required(VERSION 3.4.3)  # for CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS

##
# TARGET:
#
    Add_library(${sConsoleViewLibraryTargetName} SHARED )
    MESSAGE(STATUS "Shared library project")

    set_target_properties(${sConsoleViewLibraryTargetName} PROPERTIES
            #ARCHIVE_OUTPUT_DIRECTORY ${sOutputDir}/bin
            #LIBRARY_OUTPUT_DIRECTORY ${sOutputDir}/bin
            #RUNTIME_OUTPUT_DIRECTORY ${sOutputDir}/bin
            WINDOWS_EXPORT_ALL_SYMBOLS WIN32
            )


##
# INCLUDES:
#
	# Sources files path variables declaration
	set( sConsoleViewLibraryIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" )
	MESSAGE(STATUS "INCLUDE_DIR: ${sConsoleViewLibraryIncludeDir}")
    target_include_directories(${sConsoleViewLibraryTargetName} PUBLIC ${sConsoleViewLibraryIncludeDir})

	set( sConsoleViewLibrarySourceDir "${CMAKE_CURRENT_SOURCE_DIR}" )
	MESSAGE(STATUS "SOURCE_DIR: ${sConsoleViewLibrarySourceDir}")
    target_include_directories(${sConsoleViewLibraryTargetName} PUBLIC ${sConsoleViewLibrarySourceDir})
	

##
# SOURCE FILES RESEARCH
#
    #Research of .h/.cpp files
	file(GLOB_RECURSE sLibrarySourceFiles  ${sConsoleViewLibraryIncludeDir}/*.h ${sConsoleViewLibrarySourceDir}/*.cpp)
	group_files(sLibrarySourceFiles)

    target_sources(${sConsoleViewLibraryTargetName} PUBLIC ${sLibrarySourceFiles})



	
