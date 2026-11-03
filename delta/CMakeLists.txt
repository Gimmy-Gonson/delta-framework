project(DeltaFramework LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED CONFIG)
find_package(glm REQUIRED CONFIG)

add_library(${PROJECT_NAME}
    src/delta.cpp
    src/graphics/graphics.cpp
    src/utils/readFile.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glad
    glm::glm
)
