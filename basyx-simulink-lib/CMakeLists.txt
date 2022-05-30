cmake_minimum_required(VERSION 3.20)

project(basyx-simulink-interface
    VERSION
      0.0.1
)


# add_subdirectory(libs)


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


# 1st Block

INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR})

set(CPP_FILE RegistryConnectorBlock)

add_library(RegistryConnectorBlock SHARED src/registryConnectorBlock.cpp ${CMAKE_SOURCE_DIR}/Matlabdef.def)

target_link_libraries(RegistryConnectorBlock
    PUBLIC
      ${MATLAB_LIBRARIES}
      # urlHandler:urlHandler
      # basyxConnector:basyxconnector
      
)
# if(WIN32)
#   if (CMAKE_MINGWS)
      SET_TARGET_PROPERTIES(${CPP_FILE} PROPERTIES SUFFIX .mexw64)
      SET_TARGET_PROPERTIES(${CPP_FILE} PROPERTIES PREFIX "")
#   else(CMAKE_CL_64)
#       SET_TARGET_PROPERTIES(${CPP_FILE} PROPERTIES SUFFIX .mexw32)
#   endif(CMAKE_CL_64)
# else(WIN32)
#   if (CMAKE_SIZEOF_VOID_P MATCHES "8")
#       SET_TARGET_PROPERTIES(${CPP_FILE} PROPERTIES SUFFIX .mexa64 PREFIX "")
#   else(CMAKE_SIZEOF_VOID_P MATCHES "8")
#       SET_TARGET_PROPERTIES(${CPP_FILE} PROPERTIES SUFFIX .mexglx PREFIX "")
#   endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
# endif(WIN32)


# install to /bin by default
# install(TARGETS ${CPP_FILE} DESTINATION ${CMAKE_SOURCE_DIR}/bin)

set_target_properties(${CPP_FILE} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/simulink
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
)