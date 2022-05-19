# https://www.mathworks.com/matlabcentral/fileexchange/45522-mex_cmake

cmake_minimum_required(VERSION 3.20)

project(basyx-simulink-interface
    VERSION
      0.0.1
)


add_subdirectory(libs)


add_executable(RegistryConnectorBlock src/registryConnectorBlock.cpp)

link_libraries(
    PUBLIC
      external/Matlab/simstruc.h
)

target_link_libraries(RegistryConnectorBlock
    PUBLIC
      urlHandler:urlHandler
      basyxConnector:basyxconnector
      
)