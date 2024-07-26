add_custom_target(COPY_ASSETS
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_LIST_DIR}/imgs 
    ${CMAKE_CURRENT_LIST_DIR}/maps 
    ${CMAKE_CURRENT_BINARY_DIR}/assets
)
