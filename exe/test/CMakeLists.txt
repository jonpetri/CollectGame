MESSAGE(STATUS " ") #Display an empty line
MESSAGE(STATUS "* Boost Unit Test :")

## 
#  Boost unit_test_framework  find_package
#

if (WIN32)
    #If you run into issues looking for Boost library on windows, this may help:
    #set(BOOST_ROOT "C:/DEV/TOOLS/Boost/boost" CACHE STRING "Boost root directory")
    #set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib" CACHE STRING "Boost lib directory")
endif (WIN32)
 
#If you run into issues with CMake looking for incorrect library names, this may help:
#add_definitions(-DBOOST_ALL_NO_LIB)  # tell the compiler to undefine this boost macro
find_package(Boost COMPONENTS unit_test_framework )



if (NOT Boost_UNIT_TEST_FRAMEWORK_FOUND)
    MESSAGE(STATUS "Boost unit_test_framework not found, the unit test exe can't be build")


else ()

    # unit test building is optional:
    option(EXE_Build_boost_Unit_Test "Build the Boost Unit Test for the executable" ${Boost_UNIT_TEST_FRAMEWORK_FOUND})

    if(EXE_Build_boost_Unit_Test)

        message(STATUS "Boost Include: ${Boost_INCLUDE_DIR}")
        message(STATUS "Boost Library dirs: ${Boost_LIBRARY_DIRS}")
        message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")
        # These commands will ensure that Boost libraries (all) are linked dynamically:
        set(Boost_USE_STATIC_LIBS        OFF)
        set(Boost_USE_MULTITHREADED      ON)
        set(Boost_USE_STATIC_RUNTIME     OFF)
        set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries

        enable_testing()

    ##
    # TESTED PROJECT:
    #
        SET(sTestedTargetName ${sCollectGameExeTargetName})
    ##
    # Sources files path variables declaration
    #
        set( sUnitTestIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" )
        MESSAGE(STATUS "INCLUDE_DIR: ${sUnitTestIncludeDir}")


    ##
    # SOURCE FILES RESEARCH
    #
        file(GLOB_RECURSE sUnitTestSourceFiles  ${sUnitTestIncludeDir}/*.h ${sUnitTestIncludeDir}/*.cpp)
        group_files(sDemoSourceFiles ${sUnitTestSourceFiles})
        list(REMOVE_ITEM sUnitTestSourceFiles "${sUnitTestIncludeDir}/mockup/demo.cpp")
        #target_sources(${sBoostUnitTestTargetName} PUBLIC ${sUnitTestSourceFiles})  # Doesn't work with Cmake version 3.5.2, which I use for cross compiling (MXE)


    ##
    # TEST PROJECT:
    #
        SET(sBoostUnitTestTargetName "${sTestedTargetName}_UnitTest")

        add_executable(${sBoostUnitTestTargetName} ${sUnitTestSourceFiles} )
        ADD_TEST(${sBoostUnitTestTargetName} ${sBoostUnitTestTargetName})


    ##
    # INCLUDES:
    #
        target_include_directories(${sBoostUnitTestTargetName} PUBLIC ${sUnitTestIncludeDir})


    ##
    # TESTED PROJECT's DATA:
    #
        get_target_property(sTestedIncludes ${sTestedTargetName} INCLUDE_DIRECTORIES)
        MESSAGE(STATUS  "sTestedIncludes = ${sTestedIncludes}")
        target_include_directories(${sBoostUnitTestTargetName} PUBLIC ${sTestedIncludes})

        get_target_property(sTestedSources ${sTestedTargetName} SOURCES)
        list(GET sTestedIncludes 0 sTestedFirstInclude)
        list(REMOVE_ITEM sTestedSources "${sTestedFirstInclude}/main.cpp")
        target_sources(${sBoostUnitTestTargetName} PUBLIC ${sTestedSources})


        # Definition of exe files output directory
        MESSAGE(STATUS  "sTestedTargetName = ${sTestedTargetName}")
        #get_target_property(sTestDebugBinDir ${sTestedTargetName} LIBRARY_OUTPUT_DIRECTORY_DEBUG)       # Doesn't work with Cmake version 3.5.2, which I use for cross compiling (MXE)
        #get_target_property(sTestRealeaseBinDir ${sTestedTargetName} LIBRARY_OUTPUT_DIRECTORY_REALEASE)  # Doesn't work with Cmake version 3.5.2, which I use for cross compiling (MXE)

        set(sTestDebugBinDir "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/../test")
        set(sTestRealeaseBinDir "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/../test")

        #file(MAKE_DIRECTORY ${sTestBinDir})
        set_target_properties(${sBoostUnitTestTargetName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${sTestDebugBinDir}
            RUNTIME_OUTPUT_DIRECTORY_REALEASE ${sTestRealeaseBinDir}
            RUNTIME_OUTPUT_DIRECTORY ${sTestDebugBinDir}
            )


    ##
    # BOOST
    #
        target_include_directories(${sBoostUnitTestTargetName} PUBLIC "${Boost_INCLUDE_DIR}")
        target_link_libraries(${sBoostUnitTestTargetName} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})


    ##
    # Copy of test data folder
    #
        #add_custom_target(copy-test-folder ALL
        #COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${sTestOutputDir}/data)



    ##
    # COVERAGE
    #
        SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
        SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov --coverage")
        set_target_properties(${sBoostUnitTestTargetName} PROPERTIES COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})
        #target_compile_options(${sBoostUnitTestTargetName} PUBLIC ${GCC_COVERAGE_COMPILE_FLAGS})
        set_target_properties(${sBoostUnitTestTargetName} PROPERTIES LINK_FLAGS ${GCC_COVERAGE_LINK_FLAGS})

  
    endif()

endif()


    MESSAGE(STATUS " ")


