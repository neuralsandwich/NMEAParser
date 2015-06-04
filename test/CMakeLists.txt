enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/lib")

set(LIBS ${LIBS} ${CHECK_LIBRARIES} NMEAParser)

set(test_sources
 test.c
 create_delete_parser.c
)

add_executable(ParseTest parse_test.c)
target_link_libraries(ParseTest ${LIBS})

add_test(ParseTests ParseTest)
