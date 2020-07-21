cmake_minimum_required(VERSION 3.5)

project(AudioEditor-AU LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_CXX_STANDARD 11)

#set(SRC_LIST "*.cpp")
#set(HEAD_LIST "*.h")
file(GLOB source_files "*.cpp")
file(GLOB head_files "*.cpp")
add_executable(AudioEditor-AU ${source_files} ${head_files})

target_link_libraries(AudioEditor-AU PRIVATE Qt5::Widgets)
