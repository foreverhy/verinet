cmake_minimum_required(VERSION 3.0)
set(SOURCE_FILES EventLoop.cc)

set(INS_HEADERS EventLoop.h nocopyable.h Log.h)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(verinet ${SOURCE_FILES})


install(TARGETS verinet DESTINATION lib)
install(FILES  ${INS_HEADERS} DESTINATION include)


