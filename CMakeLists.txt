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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -g4")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(EXECUTABLE_NAME "index")
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    set(EXECUTABLE_NAME "my_sdl2_project")
endif()

add_executable(${EXECUTABLE_NAME} main.cpp)

if(NOT EMSCRIPTEN)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} mylibrary)
else()
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL2 SDL2_image SDL2_ttf)
endif()

install(
    TARGETS ${EXECUTABLE_NAME}
    ARCHIVE
        DESTINATION runtime
    LIBRARY
        DESTINATION runtime
    RUNTIME
        DESTINATION runtime
    INCLUDES 
        DESTINATION runtime
)

if(EMSCRIPTEN)
    install(FILES ${CMAKE_BINARY_DIR}/bin/${EXECUTABLE_NAME}.wasm
                  ${CMAKE_BINARY_DIR}/bin/${EXECUTABLE_NAME}.js
                  ${CMAKE_BINARY_DIR}/bin/${EXECUTABLE_NAME}.wasm.map
            DESTINATION runtime)
endif()