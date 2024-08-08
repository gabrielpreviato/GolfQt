
target_sources(${PROJECT_NAME}
    PRIVATE
    GolfKeyboard.cpp
    GolfMouse.cpp
    GolfControls.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

