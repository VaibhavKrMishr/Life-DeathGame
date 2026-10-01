cmake_minimum_required(VERSION 3.20)
project(GameOfLife VERSION 1.0.0 LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable common warnings
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
endif()

# Include FetchContent for dependencies
include(FetchContent)

# Fetch SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
# Don't build SFML examples or docs
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)

# Fetch nlohmann/json for serialization
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
set(JSON_BuildTests OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(json)

# Setup include directories
include_directories(include)

# Define source files
set(SOURCES
    src/main.cpp
    src/Grid.cpp
    src/Renderer.cpp
    src/Simulation.cpp
    src/Pattern.cpp
    src/Statistics.cpp
    src/Input.cpp
    src/Camera.cpp
    src/Serialization.cpp
)

# We will create empty/stub files for these if they don't exist yet, 
# so CMake won't fail when configuring for the first time.
foreach(SRC_FILE ${SOURCES})
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}")
        file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}" "")
    endif()
endforeach()

# Add the main executable
add_executable(GameOfLife ${SOURCES})

# Link libraries
target_link_libraries(GameOfLife PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system 
    nlohmann_json::nlohmann_json
)

# ----------------- Testing -----------------
enable_testing()

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# We'll add the test executable later when we have tests.
add_executable(GameOfLifeTests 
    tests/main_test.cpp 
    src/Grid.cpp 
    src/Simulation.cpp
)
target_link_libraries(GameOfLifeTests PRIVATE GTest::gtest_main nlohmann_json::nlohmann_json)
add_test(NAME GameOfLifeTests COMMAND GameOfLifeTests)
