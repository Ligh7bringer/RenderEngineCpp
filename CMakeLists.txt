#require recent cmake
cmake_minimum_required(VERSION 3.9)
#name of the project
project(RenderEngine)

#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#set up glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw)

#set compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

#include dirs
include_directories(src/
                    src/engine/
                    src/models/
                    src/shaders/
                    src/textures/
                    src/utilities/
                    src/entities/
                    lib/glad/include/
                    lib/glfw/include/
                    lib/glm/
                    lib/stb/)

#sources
file(GLOB VENDORS_SOURCES lib/glad/src/glad.c)
file(GLOB PROJECT_HEADERS   src/*.h
                            src/engine/*.h
                            src/models/*.h
                            src/shaders/*.h
                            src/textures/*.h
                            src/utilities/*.h
                            src/entities/*.h)
file(GLOB PROJECT_SOURCES   src/*.cpp
                            src/engine/*.cpp
                            src/models/*.cpp
                            src/shaders/*.cpp
                            src/textures/*.cpp
                            src/utilities/*.cpp
                            src/entities/*.cpp)
file(GLOB PROJECT_SHADERS   src/Shaders/*.comp
                            src/Shaders/*.frag
                            src/Shaders/*.geom
                            src/Shaders/*.vert)
file(GLOB PROJECT_CONFIGS   CMakeLists.txt
                            README.md
                            .gitattributes
                            .gitignore
                            .gitmodules)

#source groups
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

#target for copying resources to build dir
#copies res folder in the correct location based on OS and/or compiler
if(UNIX)
    message("Detected Linux! Copying resources to bin/build/...")
    add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/res" ${CMAKE_BINARY_DIR}/bin/res)
elseif(MSVC)
    message("Detected MSCV! Copying resources....")
    add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
else() #this is probably the wrong destination dir
    message("Not Linux or MSVC! Copying resources...")
    add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}/res)
endif()

#executable
add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
        ${VENDORS_SOURCES})
#link libraries
target_link_libraries(${PROJECT_NAME} glfw
        ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
#set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

#make sure resources are copied every time the project is built
add_dependencies(${PROJECT_NAME} copy_resources)
