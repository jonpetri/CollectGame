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
    option(libConsoleView_Build_boost_Unit_Test "Build the Boost Unit Test executable" ${Boost_UNIT_TEST_FRAMEWORK_FOUND})

    if(libConsoleView_Build_boost_Unit_Test)

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
        SET(sTestedTargetName ${sConsoleViewLibraryTargetName})



    ##
    # TEST PROJECT:
    #
        SET(sBoostUnitTestTargetName "${sTestedTargetName}_UnitTest")

        add_executable(${sBoostUnitTestTargetName} )
        ADD_TEST(${sBoostUnitTestTargetName} ${sBoostUnitTestTargetName})


    ##
    # INCLUDES:
    #
        set( sUnitTestIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" )
        MESSAGE(STATUS "INCLUDE_DIR: ${sUnitTestIncludeDir}")
        target_include_directories(${sBoostUnitTestTargetName} PUBLIC ${sUnitTestIncludeDir})


    ##
    # SOURCE FILES RESEARCH
    #
        file(GLOB_RECURSE sUnitTestSourceFiles  ${sUnitTestIncludeDir}/*.h ${sUnitTestIncludeDir}/*.cpp)
        group_files(sUnitTestSourceFiles)
        target_sources(${sBoostUnitTestTargetName} PUBLIC ${sUnitTestSourceFiles})
	

    ##
    # TESTED PROJECT's DATA:
    #
        get_target_property(sTestedSources ${sTestedTargetName} SOURCES)
        target_sources(${sBoostUnitTestTargetName} PUBLIC ${sTestedSources})

        get_target_property(sTestedIncludes ${sTestedTargetName} INCLUDE_DIRECTORIES)
        MESSAGE(STATUS  "sTestedIncludes = ${sTestedIncludes}")
        include_directories (${sTestedIncludes})

        # Definition of exe files output directory
        if( CMAKE_BUILD_TYPE MATCHES Release )
            set(sTestedBinDir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
        else()
            set(sTestedBinDir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
        endif()
        #get_target_property(sTestedBinDir ${sTestedTargetName} LIBRARY_OUTPUT_DIRECTORY)
        set(sTestBinDir "${sTestedBinDir}/../test")
        MESSAGE(STATUS  "sTestBinDir = ${sTestBinDir}")
        file(MAKE_DIRECTORY ${sTestBinDir})
        set_target_properties(${sBoostUnitTestTargetName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${sTestBinDir})



    ##
    # BOOST
    #
        INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
        LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
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

