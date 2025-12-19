cmake_minimum_required(VERSION 3.16)

project(keyboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(KEYBOARD_SOURCES
    src/keyboard.cpp
    src/keyboard_button.cpp
    src/keyboard_data.cpp
    src/keyboard_window.cpp
)

add_library(keyboard_lib STATIC ${KEYBOARD_SOURCES})
target_link_libraries(keyboard_lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(manual_test src/manual_test.cpp)
target_link_libraries(manual_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets keyboard_lib)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets keyboard_lib)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

qt_finalize_executable(${PROJECT_NAME})