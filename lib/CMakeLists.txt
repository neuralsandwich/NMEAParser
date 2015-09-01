set (SOURCES NMEAParser.cpp NMEAMessage.cpp)
set (INCLUDES NMEA.h NMEAParser.h)

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_library (NMEAParser SHARED "${SOURCES}" "${INCLUDES}")
add_library (NMEAParserStatic STATIC "${SOURCES}" "${INCLUDES}")

install (TARGETS NMEAParser DESTINATION lib)
install (TARGETS NMEAParserStatic DESTINATION lib)
install (FILES NMEA.h DESTINATION include)
