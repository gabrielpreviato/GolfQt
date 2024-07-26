
target_sources(${PROJECT_NAME}
   PRIVATE
    #    Engine.cpp
    GolfEngine.cpp
)

add_subdirectory(physics)
add_subdirectory(structures)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

