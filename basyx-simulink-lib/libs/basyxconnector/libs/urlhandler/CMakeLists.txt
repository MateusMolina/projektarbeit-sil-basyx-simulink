cmake_minimum_required(VERSION 3.20)

project(urlhandler
	VERSION
		0.1.0
)

add_library(${PROJECT_NAME}
	STATIC
		src/urlHandler.cpp
)

add_library(urlHandler::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)


target_compile_features(${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)

if(BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()
