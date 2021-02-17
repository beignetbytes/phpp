# CMakeList.txt : CMake project for time_seriescpp, include source and define
# project specific logic here.
#



add_executable(phpp_examples "interfaces.hpp" "phpp_examples.cpp" "phpp_examples.hpp")

target_compile_features(phpp_examples PRIVATE cxx_std_17)

message(STATUS "Compiling using toolset: ${CMAKE_CXX_COMPILER_ID}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")    
    if(CMAKE_BUILD_TYPE MATCHES "Release")
        message(STATUS "Setting release flags")
        target_compile_options(phpp_examples PRIVATE -O3 -Wall -Wextra -Wold-style-cast)
    else()
        message(STATUS "Setting debug flags")
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            target_compile_options(phpp_examples PRIVATE -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -Wall -Wextra -Wold-style-cast -DTSL_DEBUG -UNDEBUG)  
        else()
            target_compile_options(phpp_examples PRIVATE -Wall -Wextra -Wold-style-cast -DTSL_DEBUG -UNDEBUG)  
        endif()
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if(CMAKE_BUILD_TYPE MATCHES "Release")
        target_compile_options(phpp_examples PRIVATE /O2 /bigobj /WX /W3 /DTSL_DEBUG /UNDEBUG)
    else()
        target_compile_options(phpp_examples PRIVATE /bigobj /WX /W3 /DTSL_DEBUG /UNDEBUG)
    endif()
endif()

target_link_libraries(phpp_examples ${CMAKE_DL_LIBS} phpp::plugins)

add_library(extlib1 SHARED
    interfaces.hpp
	extlib1/extlib1.hpp
	extlib1/extlib1.cpp
)
set_property(TARGET extlib1 PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(extlib1 PRIVATE phpp::plugins)  

add_library(extlib2 SHARED
    interfaces.hpp
	extlib2/extlib2.hpp
	extlib2/extlib2.cpp
)

target_link_libraries(extlib2 PRIVATE phpp::plugins)  

set_property(TARGET extlib2 PROPERTY POSITION_INDEPENDENT_CODE ON)
