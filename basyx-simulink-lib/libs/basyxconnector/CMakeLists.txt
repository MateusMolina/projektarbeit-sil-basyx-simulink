cmake_minimum_required(VERSION 3.20)

project(basyxconnector
	VERSION 
		0.0.1
)

add_library(${PROJECT_NAME}
	src/registryServerProvider.cpp
	src/aasServerConnector.cpp
)

add_library(basyxConnector::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(libs)

# External Dep
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})



target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${JSONCPP_LIBRARIES} 
		urlHandler::urlhandler
		httpClient::httpclient
)

target_compile_features(${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)

if(BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()