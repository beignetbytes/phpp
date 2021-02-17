# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

project(phpp-plugins VERSION 0.1.0 LANGUAGES CXX)
include(GNUInstallDirs)


# set up extern folder if it doesnt exist
if(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/extern/depsrc/" )    
    message(STATUS "setting up extern directory")    
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/extern/depsrc)
endif()

#pull and build googletest if needed
if(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/extern/deps/googletest/")
    message(STATUS "starting googletest generate and build")
    execute_process(COMMAND git clone https://github.com/google/googletest.git
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/extern/depsrc
    )
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/extern/depsrc/googletest/release)

    execute_process(COMMAND cmake ..
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/extern/depsrc/googletest/release
    )

    execute_process(COMMAND make
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/extern/depsrc/googletest/release
    )

    execute_process(COMMAND cmake --install . --prefix ${CMAKE_SOURCE_DIR}/extern/deps/googletest
       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/extern/depsrc/googletest/release
    )



endif()

set(GTEST_DIR "${CMAKE_SOURCE_DIR}/extern/deps/googletest/${CMAKE_INSTALL_LIBDIR}/cmake/GTest/")

add_library(phpp INTERFACE)

add_library(phpp::plugins ALIAS phpp)

target_include_directories(phpp INTERFACE
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

list(APPEND phpp_headers 
"${CMAKE_CURRENT_SOURCE_DIR}/include/phpp/phpp_interface.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/include/phpp/phpp_handler.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/include/phpp/phpp_libhandler.hpp"
)

target_sources(phpp INTERFACE "$<BUILD_INTERFACE:${phpp_headers}>")


# Installation (only compatible with CMake version >= 3.3)
if(${CMAKE_VERSION} VERSION_GREATER "3.2")
    include(CMakePackageConfigHelpers)

    ## Install include directory
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/phpp"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    ## Create and install phpp-pluginsConfig.cmake
    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/phpp-pluginsConfig.cmake.in"
                                  "${CMAKE_CURRENT_BINARY_DIR}/phpp-pluginsConfig.cmake"
                                  INSTALL_DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/phpp-plugins")

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/phpp-pluginsConfig.cmake"
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/phpp-plugins")



    ## Create and install phpp-pluginsTargets.cmake
    install(TARGETS phpp
            EXPORT phpp-pluginsTargets)

    install(EXPORT phpp-pluginsTargets
            NAMESPACE phpp::
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/phpp-plugins")


    set(CMAKE_SIZEOF_VOID_P_BACKUP ${CMAKE_SIZEOF_VOID_P})
    unset(CMAKE_SIZEOF_VOID_P)
    write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/phpp-pluginsConfigVersion.cmake"
                                     COMPATIBILITY SameMajorVersion)
    set(CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P_BACKUP})

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/phpp-pluginsConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/phpp-plugins")
endif()

add_subdirectory(examples)
add_subdirectory(tests)