MESSAGE(STATUS " ")
MESSAGE(STATUS "* EXECUTABLE")

##
# EXECUTABLE'S NAME
#

    MESSAGE(STATUS "Name: ${sCollectGameExeTargetName}")
	

##
# Sources files path variables declaration
#
    set(sExeSourceDir "${CMAKE_CURRENT_SOURCE_DIR}")
    MESSAGE(STATUS "SOURCE_DIR: ${sExeSourceDir}")

##
# SOURCE FILES RESEARCH
#
    #Research of .h/.cpp files
    file(GLOB_RECURSE sExeSourceFiles  ${sExeSourceDir}/*.h ${sExeSourceDir}/*.cpp)
    group_files(sExeSourceFiles)
    #target_sources(${sCollectGameExeTargetName} PUBLIC ${sExeSourceDir})  # Doesn't work with Cmake version 3.5.2, which I use for cross compiling (MXE)

##
# TARGET:
#
    add_executable(${sCollectGameExeTargetName} ${sExeSourceFiles} )

##
# INCLUDES:
#
    target_include_directories(${sCollectGameExeTargetName} PUBLIC ${sExeSourceDir})
  
##
# LIBRARIES LINK:
#
    # ConsoleView Library
    # -------------------
    SET(sLinkedLib1TargetName ${sConsoleViewLibraryTargetName})
    MESSAGE(STATUS "Link to lybrary: ${sLinkedLib1TargetName}")
    get_target_property(sLinkedLib1Includes ${sLinkedLib1TargetName} INCLUDE_DIRECTORIES)
    target_include_directories(${sCollectGameExeTargetName} PUBLIC ${sLinkedLib1Includes})
    target_link_libraries(${sCollectGameExeTargetName}  ${sLinkedLib1TargetName})

    MESSAGE(STATUS "sLinkedLib1Includes: ${sLinkedLib1Includes}")
