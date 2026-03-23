# Main executable for Chess Variant Cell-DEVS simulation
add_executable(chess_variant main.cpp)

# Include directories
target_include_directories(chess_variant PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CADMIUM_INCLUDE_DIR}
)

# Link nlohmann_json if found as package
if(nlohmann_json_FOUND)
    target_link_libraries(chess_variant PRIVATE nlohmann_json::nlohmann_json)
endif()
