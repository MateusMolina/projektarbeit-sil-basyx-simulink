project(urlhandler-tests)

include(FetchContent)

add_executable(${PROJECT_NAME}
        main.cpp
)


set(ALL_TESTS
      ${PROJECT_SOURCE_DIR}/test_urlHandler.cpp 
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

FetchContent_MakeAvailable(testgoogle )

include(GoogleTest)


target_link_libraries(${PROJECT_NAME}
      urlHandler::urlhandler
      gtest
      gmock
)


gtest_discover_tests(${PROJECT_NAME})