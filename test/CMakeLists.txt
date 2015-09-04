enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/lib")

set(GOOGLIBS ${LIBS} gtest gtest_main)

add_executable(ParseTimeStamp_String_Test ParseTimeStamp_String_Test.cpp)
target_link_libraries(ParseTimeStamp_String_Test ${GOOGLIBS} NMEAParser)

add_executable(ParseTimeStamp_String_String_Test ParseTimeStamp_String_String_Test.cpp)
target_link_libraries(ParseTimeStamp_String_String_Test ${GOOGLIBS} NMEAParser)

add_executable(ValidateChecksum_Test ValidateChecksum_Test.cpp)
target_link_libraries(ValidateChecksum_Test ${GOOGLIBS} NMEAParser)

add_executable(ParseTalkerID_Test ParseTalkerID_Test.cpp)
target_link_libraries(ParseTalkerID_Test ${GOOGLIBS} NMEAParser)

add_executable(ParseMessageType_Test ParseMessageType_Test.cpp)
target_link_libraries(ParseMessageType_Test ${GOOGLIBS} NMEAParser)

add_executable(ParseFloat_Test ParseFloat_Test.cpp)
target_link_libraries(ParseFloat_Test ${GOOGLIBS} NMEAParser)

add_test(NAME ParseTimeStamp_String_Test COMMAND ParseTimeStamp_String_Test)
add_test(NAME ParseTimeStamp_String_String_Test COMMAND ParseTimeStamp_String_String_Test)
add_test(NAME ValidateChecksum COMMAND ValidateChecksum_Test)
add_test(NAME ParseTalkerID COMMAND ParseTalkerID_Test)
add_test(NAME ParseMessageType COMMAND ParseMessageType_Test)
add_test(NAME ParseFloat COMMAND ParseFloat_Test)
