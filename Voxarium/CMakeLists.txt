cmake_minimum_required(VERSION 2.8)

project(Voxarium)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/nvidia/current/libGL.so.319.82)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(glimac)

file(GLOB DIRECTORIES "Vox*")

foreach(Vox ${DIRECTORIES})
    add_subdirectory(${Vox})
endforeach()

file(	GLOB_RECURSE 
		source_file 
		Vox/src/*.cpp 
		Vox/include/*.hpp)

add_executable(Voxarium ${source_file})

target_link_libraries (Voxarium glimac)
target_link_libraries (Voxarium ${SDL_LIBRARY})
target_link_libraries (Voxarium ${OPENGL_LIBRARIES})
target_link_libraries (Voxarium ${GLEW_LIBRARY})
