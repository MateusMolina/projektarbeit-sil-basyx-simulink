
cmake_minimum_required(VERSION 3.20)

project(httpclient
	VERSION 
		0.0.1
)

add_library(${PROJECT_NAME}  
	STATIC
		src/curlHttpConnection.cpp
)

# Find Curl
find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR}) # is this line really needed?

add_library(httpClient::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${CURL_LIBRARIES} 
		urlHandler::urlhandler
)


target_compile_features(${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)

# if(BUILD_TESTING)
# 	add_subdirectory(tests)
# endif()
