add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${PROJECT_NAME})

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
                  ${CMAKE_BINARY_DIR}/bin/${EXECUTABLE_NAME}.data
            DESTINATION runtime)
endif()
