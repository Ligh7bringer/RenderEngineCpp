# require recent cmake
cmake_minimum_required(VERSION 3.9)
project(RenderEngine)

# Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# set up glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw)

# sources
file(GLOB VENDORS_SOURCES lib/glad/src/glad.c)

# header files
file(
  GLOB
  PROJECT_HEADERS
  src/*.h
  src/engine/*.h
  src/models/*.h
  src/shaders/*.h
  src/textures/*.h
  src/utilities/*.h
  src/entities/*.h
  src/terrains/*.h
  src/guis/*.h
  src/skybox/*.h
  src/water/*.h
  src/particles/*.h)

# implementation files
file(
  GLOB
  PROJECT_SOURCES
  src/*.cpp
  src/engine/*.cpp
  src/models/*.cpp
  src/shaders/*.cpp
  src/textures/*.cpp
  src/utilities/*.cpp
  src/entities/*.cpp
  src/terrains/*.cpp
  src/guis/*.cpp
  src/skybox/*.cpp
  src/water/*.cpp
  src/particles/*.cpp)

# shaders
file(GLOB PROJECT_SHADERS src/Shaders/*.comp src/Shaders/*.frag
     src/Shaders/*.geom src/Shaders/*.vert)

# everything else which is not code
file(
  GLOB
  PROJECT_CONFIGS
  CMakeLists.txt
  README.md
  .gitattributes
  .gitignore
  .gitmodules)

# source groups
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

# executable
add_executable(
  ${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SHADERS}
                  ${PROJECT_CONFIGS} ${VENDORS_SOURCES})
# link libraries
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DGLFW_INCLUDE_NONE
                           -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE src/
          src/engine/
          src/models/
          src/shaders/
          src/textures/
          src/utilities/
          src/entities/
          src/terrains/
          src/guis/
          src/skybox/
          src/water/
          src/particles/
          lib/glad/include/
          lib/glfw/include/
          lib/glm/
          lib/stb/)

# copy resources to build/bin dir
add_custom_target(
  copy_resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res"
          ${OUTPUT_DIRECTORY}/res)
add_dependencies(${PROJECT_NAME} copy_resources)


