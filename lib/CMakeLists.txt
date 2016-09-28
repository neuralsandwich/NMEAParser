if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/NMEAMessage.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/NMEAParser.cpp
  )
set(INCLUDES
  NMEA.h
  NMEAParser.cpp)

if(STATICLIB)
  add_library (NMEAParserStatic STATIC ${SOURCES}  ${INCLUDES})
  install (TARGETS NMEAParserStatic DESTINATION lib)
else(STATICLIB)
  add_library (NMEAParser SHARED ${SOURCES} ${INCLUDES})
  target_link_libraries(NMEAParser ${CMAKE_DL_LIBS})
  install (TARGETS NMEAParser DESTINATION lib)
endif(STATICLIB)

install (FILES NMEA.h DESTINATION include)
