project(basyxconnector-tests)


find_package(GTest REQUIRED)
find_library(GMOCK_LIBRARY_MAIN 
                NAMES gmock_main 
                      libgmock_main  
                      libgmock_main.a  
                PATHS "${GMOCK_DIR}")

find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        mock
)
set(ALL_TESTS
    ${PROJECT_SOURCE_DIR}/mock/mock_httpConnection.hpp 
    ${PROJECT_SOURCE_DIR}/test_registryServerProvider.cpp 
)

target_sources(${PROJECT_NAME}
    PRIVATE
      ${ALL_TESTS} 
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        basyxConnector::basyxconnector
        gmock_main
        gmock
        gtest_main
        gtest
        pthread
)
gtest_discover_tests(${PROJECT_NAME})