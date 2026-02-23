cmake_minimum_required(VERSION 3.2...3.27.5)

project(super_mario)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=utf-8")

option(USE_QT "Build with Qt GUI instead of console" OFF)

if(USE_QT)
	set(CMAKE_AUTOMOC ON)
	find_package(Qt6 REQUIRED COMPONENTS Widgets)
	set(SOURCES qt_main.cpp)
else()
	set(SOURCES main.cpp)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

if(USE_QT)
	target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
endif()

if(NOT USE_QT)
	add_subdirectory(os_controls)
endif()
add_subdirectory(controller)
add_subdirectory(levels)
add_subdirectory(model)
add_subdirectory(objects)
add_subdirectory(ui)

