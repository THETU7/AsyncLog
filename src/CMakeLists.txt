set(SRC_SOURCE LogStream.cc Logging.cc LogFile.cc FixedBuffer.cc)


add_library(AsyncLog ${SRC_SOURCE})

add_executable(AsyncLog main.cc)
target_link_libraries(AsyncLog LogStream pthread)
