project(Cool LANGUAGES C CXX)

find_package(SDL3 REQUIRED CONFIG)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    DeltaFramework
    SDL3::SDL3
)
