
target_sources(${PROJECT_NAME}
    PRIVATE
    Structure.cpp
    GolfBall.cpp
    SpatialHashMap.cpp
    FloorHashMap.cpp
    CollisionHashMap.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

