
# add_library(basyxconnector SHARED IMPORTED GLOBAL)
# set_target_properties(basyxconnector PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/basyxconnector/lib/libcurl-x64.dll)
# set_target_properties(basyxconnector PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/libs/basyxconnector/lib/libcurl.dll.a)
# set_target_properties(basyxconnector PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/libs/basyxconnector/include)


set(BLOCKS PropertySAConnectorBlock)

foreach(BLOCK ${BLOCKS})
    add_library(${BLOCK} SHARED ${BLOCK}.cpp ${CMAKE_SOURCE_DIR}/Matlabdef.def)

    target_link_libraries(${BLOCK}
        PUBLIC
        ${MATLAB_LIBRARIES}
        urlHandler::urlhandler
        httpClient::httpclient
        basyxConnector::basyxconnector
    )

    SET_TARGET_PROPERTIES(${BLOCK} PROPERTIES SUFFIX .mexw64)
    SET_TARGET_PROPERTIES(${BLOCK} PROPERTIES PREFIX "")        # Removes lib from target name

    set_target_properties(${BLOCK} PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/simulink
                        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
    )

endforeach()

add_custom_command ( TARGET PropertySAConnectorBlock POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:libcurl> $<TARGET_FILE_DIR:PropertySAConnectorBlock>
)