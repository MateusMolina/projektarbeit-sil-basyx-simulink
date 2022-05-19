project(basyxconnector-tests)

include(FetchContent)


add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        mock
)
set(ALL_TESTS
    ${PROJECT_SOURCE_DIR}/mock/mock_httpConnection.hpp 
    ${PROJECT_SOURCE_DIR}/test_registryServerConnector.cpp 
    ${PROJECT_SOURCE_DIR}/test_aasServerConnector.cpp 
)

target_sources(${PROJECT_NAME}
    PRIVATE
      ${ALL_TESTS} 
)

FetchContent_Declare(
      testgoogle
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)

FetchContent_MakeAvailable(testgoogle)

include(GoogleTest)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        gtest
        gmock
        basyxConnector::basyxconnector
        httpClient::httpclient
		urlHandler::urlhandler
        
)

# TODO find a better solution than copying the .dll dep individually
add_custom_command ( TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:libcurl> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

gtest_discover_tests(${PROJECT_NAME})