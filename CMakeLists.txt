cmake_minimum_required( VERSION 3.10 )

project( ZKSL-75-6LC C )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused -g" )
set( CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused -g" )

include_directories (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lvgl
    ${PROJECT_SOURCE_DIR}/ui
)

FILE( GLOB_RECURSE LVGL_Sources CONFIGURE_DEPENDS lvgl/*.c )
FILE( GLOB_RECURSE UI_Sources CONFIGURE_DEPENDS ui/*.c ui/*.cpp )

set( CMAKE_GENERATOR "MinGW Makefiles" )

set( SDL_FOLDER sdl2-dev-x86_64 )
set( CMAKE_FIND_ROOT_PATH ${SDL_FOLDER} )
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

set( CMAKE_BUILD_RPATH "${SDL_FOLDER}/include" )
set( CMAKE_INSTALL_RPATH ${CMAKE_BUILD_RPATH} )

include_directories( ${PROJECT_SOURCE_DIR}/${SDL_FOLDER}/include )

FILE( GLOB_RECURSE SDL_Sources CONFIGURE_DEPENDS ${SDL_FOLDER} )

add_executable( ${PROJECT_NAME} main.c ${LVGL_Sources} ${SDL_Sources} ${UI_Sources} )

target_link_libraries( ${PROJECT_NAME} -L"${PROJECT_SOURCE_DIR}/${SDL_FOLDER}/lib" SDL2 )


