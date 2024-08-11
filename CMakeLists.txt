cmake_minimum_required(VERSION 3.5.0)
project(IntelliDrive VERSION 0.1.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)

# Build SFML
add_subdirectory(vendors/sfml/)

# Collect all the source and header files
file(GLOB ALL_SOURCE_FILES src/*.cpp)
file(GLOB ALL_HEADER_FILES include/*.hpp)

# Add the main executable target
add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES} ${ALL_HEADER_FILES})

# Use C++17 standards
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Include directories
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE ${PROJECT_SOURCE_DIR}/include/
        PRIVATE ${PROJECT_SOURCE_DIR}/vendors/sfml/include/
)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Define the resource directory
set(RESOURCE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

# Create the resource directory if it doesn't exist
file(MAKE_DIRECTORY ${RESOURCE_DIR})

# Get all files in the resources directory
file(GLOB RESOURCE_FILES ${PROJECT_SOURCE_DIR}/resources/*)

# Add custom command to copy resource files
foreach(resource ${RESOURCE_FILES})
    get_filename_component(resource_name ${resource} NAME)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${resource} ${RESOURCE_DIR}/${resource_name}
            COMMENT "Copying ${resource} to ${RESOURCE_DIR}/${resource_name}"
    )
endforeach()
