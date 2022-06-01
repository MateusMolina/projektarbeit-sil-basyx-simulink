cmake_minimum_required(VERSION 3.20)

project(basyx-simulink-interface
    VERSION
      0.0.1
)

add_subdirectory(libs)

# MATLAB Dependencies
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake) # add FindMatlab module

add_definitions(/DMATLAB_MEX_FILE) #define matlab macros
add_definitions(/DMX_COMPAT_32)

find_package(Matlab REQUIRED)

IF(MATLAB_FOUND)
    message(STATUS "MATLAB Found, MATLAB MEX will be compiled.")
    # add_subdirectory(mex)
ELSE(MATLAB_FOUND)
    MESSAGE("MATLAB not found...nothing will be built.")
ENDIF(MATLAB_FOUND)

INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR})

add_subdirectory(src)