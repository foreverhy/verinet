cmake_minimum_required(VERSION 3.0)
project(verinet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")
set(PROJECT_NAME_STR verinet)

find_package(Threads REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

set(COMMON_INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/gtest_1.7.0)

# Test
#if (test)
    add_subdirectory(${PROJECT_SOURCE_DIR}/gtest-1.7.0)

    enable_testing()
    set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
    include_directories(${GTEST_ROOT}/include ${COMMON_INCLUDE})

    file(GLOB TEST_SRC ${PROJECT_SOURCE_DIR}/test/*.cc)
    add_executable(${PROJECT_TEST_NAME} ${TEST_SRC})
    target_link_libraries(${PROJECT_TEST_NAME}
        verinet 
        gtest
        gtest_main
        )
    target_link_libraries(${PROJECT_TEST_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
        )

    add_test(test1, ${PROJECT_TEST_NAME})
#endif()
