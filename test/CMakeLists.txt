add_executable (print print.c)

target_link_libraries(print LINK_PUBLIC libNMEAParser)
