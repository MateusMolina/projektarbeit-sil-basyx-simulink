# https://www.mathworks.com/matlabcentral/fileexchange/45522-mex_cmake


cmake_minimum_required(VERSION 3.10)

project(basyx-simulink-lib CXX)
# set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(Threads)
find_package(CURL REQUIRED) 

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIR})

include_directories(./include)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )


add_executable(app ./src/app.cpp)
# add_executable(runTests tests/test_httpconnection.cpp)

# target_link_libraries(app ${CURL_LIBRARIES} ${all_SRCS})
target_link_libraries(app ${PROJECT_SOURCE_DIR}/src/httpConnection.cpp ${CURL_LIBRARIES} )
# target_link_libraries(runTests ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES} ${all_SRCS})

# enable_testing()

# add_test(NAME runTests COMMAND $<TARGET_FILE:runTests>)