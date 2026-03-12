cmake_minimum_required(VERSION 3.16)
project(encoder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.10.2/macos/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCE
    src/main.cpp
    src/mainwindow.cpp
    src/file/FileEncoder.cpp
    src/file/FileScanner.cpp
    src/task/Task.cpp
)

set(HEADER
    src/mainwindow.hpp
    src/file/FileEncoder.hpp
    src/file/FileScanner.hpp
    src/task/Task.hpp
    src/settings/AppSettings.hpp
)

set(INCLUDE
    src/
    src/file
    src/settings
    src/task
)

add_executable( encoder
    ${SOURCE}
    ${HEADER}
)

target_include_directories(encoder PRIVATE ${INCLUDE})
target_link_libraries(encoder PRIVATE Qt6::Widgets)