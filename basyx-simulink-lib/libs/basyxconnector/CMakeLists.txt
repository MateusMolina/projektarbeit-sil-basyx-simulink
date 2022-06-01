cmake_minimum_required(VERSION 3.20)

project(basyxconnector
	VERSION 
		0.0.1
)

add_library(${PROJECT_NAME} 
	src/registryServerConnector.cpp
	src/aasServerConnector.cpp
	include/basyxconnector/components.hpp
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
## Working on Linux
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(JSONCPP jsoncpp)
# include_directories(${JSONCPP_INCLUDE_DIRS})

### Working on WINDOWS

#TODO make conditionals based on a WIN32 env var
add_library(jsoncpp STATIC IMPORTED)
set_target_properties(jsoncpp PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/jsoncpp/lib/libjsoncpp.a)
set_target_properties(jsoncpp PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/external/jsoncpp/include)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		jsoncpp
	PUBLIC
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