cmake_minimum_required(VERSION 3.0)
set(SOURCE_FILES Tverinet.cc)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(verinet ${SOURCE_FILES})


install(TARGETS verinet DESTINATION lib)
install(FILES  ${INS_HEADERS} DESTINATION include)


