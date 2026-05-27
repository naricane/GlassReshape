cmake_minimum_required(VERSION 3.10)

project(GlassReshape)

set(GS_SOURCES
  src/GS/Engine/Assets/MeshFactory.cpp
  src/GS/Engine/Core/Engine.cpp
  src/GS/Engine/Core/Error.cpp
  src/GS/Engine/Core/Input.cpp
  src/GS/Engine/Render/IndexBuffer.cpp
  src/GS/Engine/Render/Mesh.cpp
  src/GS/Engine/Render/Shader.cpp
  src/GS/Engine/Render/VertexArray.cpp
  src/GS/Engine/Render/VertexBuffer.cpp
  src/GS/Engine/Render/Video.cpp
  src/GS/Engine/World.cpp
  src/GS/main.cpp
)

option(GS_ASAN "Enable address sanitiser" OFF)

if(GS_ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

option(GS_UBSAN "Enable undefined behaviour sanitiser" OFF)

if(GS_UBSAN)
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
endif()

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(glm CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(GlassReshape ${GS_SOURCES} "src/glad/src/glad.c")
target_link_libraries(GlassReshape PRIVATE SDL3::SDL3 glm::glm)

target_include_directories(GlassReshape PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/glad/include
  ${CMAKE_SOURCE_DIR}/src/stb
)
