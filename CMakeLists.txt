cmake_minimum_required(VERSION 3.28)

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

# Find the necessary Qt6 packages. Add additional required components as needed.
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Use qt_standard_project_setup() if available and needed. This macro standardizes some Qt project settings.
# It's available from Qt 6.3 and later. If you're using an earlier version of Qt6, you might need to omit this.
# Check the documentation for your specific Qt version.
#if(QT_VERSION_MAJOR EQUAL 6 AND QT_VERSION_MINOR GREATER_EQUAL 3)
#    qt_standard_project_setup()
#endif()

qt_add_executable(${PROJECT_NAME})

add_subdirectory(assets)
add_subdirectory(src)

