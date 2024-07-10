cmake_minimum_required(VERSION 3.6)

project(QtGolf)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable AUTOMOC, AUTORCC, and AUTOUIC for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR "Ninja")
set(CMAKE_BUILD_TYPE "Debug")

# It's better to not hard-code the CMAKE_PREFIX_PATH in the CMakeLists.txt.
# Instead, pass it as a command-line argument to cmake or set it as an environment variable.
# set(CMAKE_PREFIX_PATH "D:/Qt/6.7.1/msvc2019_64/")

# Find the necessary Qt6 packages. Add additional required components as needed.
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Use qt_standard_project_setup() if available and needed. This macro standardizes some Qt project settings.
# It's available from Qt 6.3 and later. If you're using an earlier version of Qt6, you might need to omit this.
# Check the documentation for your specific Qt version.
if(QT_VERSION_MAJOR EQUAL 6 AND QT_VERSION_MINOR GREATER_EQUAL 3)
    qt_standard_project_setup()
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    GolfView.cpp GolfView.hpp
    GolfScene.cpp GolfScene.hpp
    GolfQt.cpp GolfQt.hpp
    Structure.cpp Structure.hpp
    Physics.cpp Physics.hpp Physics-Constants.hpp
    Line2.cpp Line2.hpp Vec2.hpp utilities.hpp
    GolfEngine.cpp GolfEngine.hpp
    SpatialHashMap.cpp SpatialHashMap.hpp
    GolfMap.cpp GolfMap.hpp
    GolfPlayer.cpp GolfPlayer.hpp
    GolfCamera.hpp
    json.hpp
    # Add .h files here if you want them to appear in IDE project structure
)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets Qt6::Gui)
