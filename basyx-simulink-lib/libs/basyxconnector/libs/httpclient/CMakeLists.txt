
cmake_minimum_required(VERSION 3.20)

project(httpclient
	VERSION 
		0.0.1
)

add_library(${PROJECT_NAME}  
	STATIC
		src/utils.cpp
		src/curlHttpConnection.cpp 
)

add_library(httpClient::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Find Curl
### WORKING ON LINUX
# find_package(CURL REQUIRED) 
# include_directories(${CURL_INCLUDE_DIR}) # is this line really needed?

# Working on WINDOWS
add_library(libcurl SHARED IMPORTED GLOBAL)
set_target_properties(libcurl PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/curl/lib/libcurl-x64.dll)
set_target_properties(libcurl PROPERTIES IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/external/curl/lib/libcurl.dll.a)
set_target_properties(libcurl PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/external/curl/include)


#TODO make conditionals based on a WIN32 env var


target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		libcurl
		urlHandler::urlhandler
)


target_compile_features(${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)


add_custom_command ( TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:libcurl> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# if(BUILD_TESTING)
# 	add_subdirectory(tests)
# endif()
