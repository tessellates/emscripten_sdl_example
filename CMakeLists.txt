cmake_minimum_required(VERSION 3.20)
project(emex VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)  # Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Make the C++ standard required

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${${PROJECT_NAME}_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME}_BINARY_DIR}/bin")

if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
endif()

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/build")

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -g4 --preload-file assets --use-preload-plugins")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(EXECUTABLE_NAME "index")
else()
    find_package(SDL2 REQUIRED CONFIG)
    find_package(SDL2_image REQUIRED CONFIG)
    find_package(SDL2_ttf REQUIRED CONFIG)
    set(EXECUTABLE_NAME driver)
endif()

find_package(glm REQUIRED CONFIG)

add_library(${PROJECT_NAME} STATIC)

if(NOT EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_image::SDL2_image-static)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_ttf::SDL2_ttf-static)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 SDL2_image SDL2_ttf)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

add_subdirectory(driver)
add_subdirectory(source)

# Copy assets to the build directory
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/driver/assets)
