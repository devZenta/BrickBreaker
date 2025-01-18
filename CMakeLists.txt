cmake_minimum_required(VERSION 3.29)
project(BrickBreaker C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "C:\\Users\\hugog\\Desktop\\Lib\\SDL2-2.30.9\\x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "C:\\Users\\hugog\\Desktop\\Lib\\SDL2_image-2.8.3\\x86_64-w64-mingw32")
set(SDL2_TTF_PATH "C:\\Users\\hugog\\Desktop\\Lib\\SDL2_ttf-2.22.0\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories( ${SDL2_INCLUDE_DIRS})
include_directories( ${SDL2_IMAGE_INCLUDE_DIRS})
include_directories( ${SDL2_TTF_INCLUDE_DIRS})

add_executable(BrickBreaker main.c
        menu.c
        menu.h
        game.c
        game.h
        utils.c
        utils.h
        menu_settings.c
        menu_settings.h
        menu_help.c
        menu_help.h
        data.c
        data.h
)

target_link_libraries(BrickBreaker ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
