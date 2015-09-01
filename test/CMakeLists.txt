enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/lib")

set(GOOGLIBS ${LIBS} gtest gtest_main)

add_executable(ParseTestDynamic parse_test.cpp)
target_link_libraries(ParseTestDynamic ${GOOGLIBS} NMEAParser)

add_executable(ParseTestStatic parse_test.cpp)
target_link_libraries(ParseTestStatic ${GOOGLIBS} NMEAParserStatic)

add_test(NAME ParseTestsDynamic COMMAND ParseTestDynamic)
add_test(NAME ParseTestsStatic COMMAND ParseTestStatic)
