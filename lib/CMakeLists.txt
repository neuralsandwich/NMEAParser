add_library (libNMEAParser NMEAParser.cpp NMEAMessage.cpp)

target_include_directories (libNMEAParser PUBLIC ${CMAKE_CURRENT_SOURE_DIR})


