
target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp
    GolfScene.cpp
    GolfQt.cpp
    GolfMap.cpp
    GolfPlayer.cpp
)

add_subdirectory(views)
add_subdirectory(engine)
add_subdirectory(widgets)
add_subdirectory(controller)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
add_dependencies(${PROJECT_NAME} COPY_ASSETS)

add_subdirectory(assets_manager)
target_link_libraries(${PROJECT_NAME} PRIVATE AssetsManager)

