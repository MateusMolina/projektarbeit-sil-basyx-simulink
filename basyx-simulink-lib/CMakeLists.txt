# https://www.mathworks.com/matlabcentral/fileexchange/45522-mex_cmake


cmake_minimum_required(VERSION 3.20)

project(basyx-simulink-lib CXX)
# set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_library(GMOCK_LIBRARY_MAIN 
                NAMES gmock_main 
                      libgmock_main  
                      libgmock_main.a  
                PATHS "${GMOCK_DIR}")


# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   # Specify the commit you depend on and update it regularly.
#   URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)


find_package(Threads)
find_package(CURL REQUIRED) 

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIR})

# link_libraries(${JSONCPP_LIBRARIES})
# file(GLOB all_SRCS
#         "${PROJECT_SOURCE_DIR}/src/*.cpp"
#         )

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(JSONCPP jsoncpp)
# include_directories(${JSONCPP_INCLUDE_DIRS})

include_directories(./include)
# include_directories(./include/httpconnection)

set(ALL_SRCS 
  ${PROJECT_SOURCE_DIR}/src/urlHandler.cpp 
  ${PROJECT_SOURCE_DIR}/src/registryServerProvider.cpp 
  ${PROJECT_SOURCE_DIR}/include/httpconnection/httpConnection.hpp  
)

# add_executable(app ./src/app.cpp)
# add_executable(runTests tests/test_httpconnection.cpp)

# target_link_libraries(app ${CURL_LIBRARIES} ${all_SRCS})
# target_link_libraries(app ${all_SRCS} ${CURL_LIBRARIES} )
# target_link_libraries(runTests ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES} ${ALL_SRCS})


#region Testing

enable_testing()


# Should use target_include_directories()
include_directories(./tests/mock)

set(ALL_TESTS
  ${PROJECT_SOURCE_DIR}/tests/test_registryServerProvider.cpp 
  ${PROJECT_SOURCE_DIR}/tests/test_urlHandler.cpp 
  ${PROJECT_SOURCE_DIR}/tests/mock/mock_httpConnection.hpp
)

add_executable(
  runTests
  ${PROJECT_SOURCE_DIR}/tests/main.cpp
)
target_link_libraries(
  runTests
  ${ALL_SRCS} 
  ${ALL_TESTS}
  ${CURL_LIBRARIES} 
  # ${JSONCPP_LIBRARIES} 
  gmock_main
  gmock
  gtest_main
  gtest
  pthread
)


# gtest_discover_tests(runTests)

# add_test(NAME runTests COMMAND $<TARGET_FILE:runTests>)
#endregion