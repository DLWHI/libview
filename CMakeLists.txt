cmake_minimum_required(VERSION 3.24)
set(GCC_COMPILE_FLAGS "-g -fdiagnostics-color=always -Wno-narrowing -std=c++20")

set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeFiles/modules")
project(test)

ADD_DEFINITIONS(${GCC_COMPILE_FLAGS})

set(SAUSE_DIR "src/")
set(TEXT_SRC main.cpp)
set(SURCES  anchored_element.cpp
            base_element.cpp
            border.cpp
            button.cpp
            canvas.cpp
            clickable.cpp
            controllable.cpp
            image.cpp
            move_animator.cpp
            text_renderer.cpp
            text.cpp
            window.cpp)
list(TRANSFORM SURCES PREPEND ${SAUSE_DIR})

add_executable(main ${TEXT_SRC})
include_directories(include
                    .)

add_library(view STATIC ${SURCES})

set(LIBS view)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(main ${LIBS} ${SDL2_LIBRARIES} "-mconsole" ${SDL2_IMAGE_LIBRARIES} SDL2_ttf::SDL2_ttf)
