# CMakeList.txt : CMake project for time_seriescpp, include source and define
# project specific logic here.
#



set(BINARY ${CMAKE_PROJECT_NAME}_tests)
enable_testing()


list(APPEND TEST_SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/phpp_tests.cpp"
) 


set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})


target_compile_features(${BINARY} PRIVATE cxx_std_17)

message(STATUS "Compiling using toolset: ${CMAKE_CXX_COMPILER_ID}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")    
    if(CMAKE_BUILD_TYPE MATCHES "Release")
        message(STATUS "Setting release flags")
        target_compile_options(${BINARY} PRIVATE -O3 -mavx2 -mpopcnt -Wall -Wextra -Wold-style-cast)
    else()
        message(STATUS "Setting debug flags")
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            target_compile_options(${BINARY} PRIVATE -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -Wall -Wextra -Wold-style-cast -DTSL_DEBUG -UNDEBUG)  
        else()
            target_compile_options(${BINARY} PRIVATE -Wall -Wextra -Wold-style-cast -DTSL_DEBUG -UNDEBUG)  
        endif()
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if(CMAKE_BUILD_TYPE MATCHES "Release")
        target_compile_options(${BINARY} PRIVATE /O2 /bigobj /WX /W3 /DTSL_DEBUG /UNDEBUG)
    else()
        target_compile_options(${BINARY} PRIVATE /bigobj /WX /W3 /DTSL_DEBUG /UNDEBUG)
    endif()
endif()


find_package(GTest REQUIRED PATHS ${GTEST_DIR}) 

target_link_libraries(${BINARY} PRIVATE phpp::plugins)

target_link_libraries(${BINARY} PUBLIC GTest::gtest pthread)

add_library(testextlib1 SHARED
    ../examples/interfaces.hpp
	../examples/extlib1/extlib1.hpp
	../examples/extlib1/extlib1.cpp
)
set_property(TARGET testextlib1 PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(testextlib1 PRIVATE phpp::plugins)  

add_library(testextlib2 SHARED
    ../examples/interfaces.hpp
	../examples/extlib2/extlib2.hpp
	../examples/extlib2/extlib2.cpp
)

target_link_libraries(testextlib2 PRIVATE phpp::plugins)  

set_property(TARGET testextlib2 PROPERTY POSITION_INDEPENDENT_CODE ON)

add_test(NAME ${BINARY} COMMAND ${BINARY})