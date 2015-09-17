enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/lib")

set(GOOGLIBS ${LIBS} gtest gtest_main)

set(TESTS
  GGAMessageParse
  GLLMessageParse
  GSAMessageParse
  GSVMessageParse
  ParseAngle
  ParseCOGM
  ParseCOGT
  ParseDifferentialCorrectionAge
  ParseDifferentialStationID
  ParseFixStatus
  ParseFloat
  ParseGeoidSeparation
  ParseHDOP
  ParseInteger
  ParseLLL
  ParseLatitude
  ParseLongitude
  ParseMSL
  ParseMagneticVariation
  ParseMessageType
  ParseModeIndicator
  ParseNavMode
  ParsePDOP
  ParseSOG
  ParseSV
  ParseSatiliteFixes
  ParseSmode
  ParseSpeed
  ParseStatus
  ParseTalkerID
  ParseTimeStamp_String
  ParseTimeStamp_String_String
  ParseVDOP
  RMCMessageParse
  VTGMessageParse
  ValidateChecksum
  )

foreach(Test ${TESTS})
  add_executable(${Test}_Test ${Test}_Test.cpp)
  target_link_libraries(${Test}_Test ${GOOGLIBS} NMEAParser)
  add_test(NAME ${Test} COMMAND ${Test}_Test)
endforeach(Test)
