set(SRC_SOURCE LogStream.cc buffer.cc Logging.cc LogFile.cc FixedBuffer.cc)


add_library(AsyncLog ${SRC_SOURCE})

add_executable(asynclog main.cc)
target_link_libraries(asynclog AsyncLog pthread)
