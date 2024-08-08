add_library(AssetsManager)

target_sources(AssetsManager
    PRIVATE
    AssetsManager.cpp
    Material.cpp
)

target_include_directories(AssetsManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(AssetsManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(AssetsManager PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
add_dependencies(AssetsManager COPY_ASSETS)
