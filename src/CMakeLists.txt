
target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp
    GolfView.cpp
    GolfScene.cpp
    GolfQt.cpp
    SpatialHashMap.cpp
    GolfMap.cpp
    GolfPlayer.cpp
    GolfWall.cpp
)

add_subdirectory(engine)
add_subdirectory(widgets)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
add_dependencies(${PROJECT_NAME} COPY_ASSETS)
