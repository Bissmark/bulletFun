cmake_minimum_required(VERSION 3.10)
project(BulletFun)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(BulletFun
    src/main.cpp
    src/player.cpp
    src/enemy.cpp
    src/enemySpawner.cpp
    src/bullet.cpp
    src/archer.cpp
    src/grunt.cpp
    src/slime.cpp
    # Add other source files here
)

# Include directories
target_include_directories(BulletFun PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link Raylib
find_package(raylib REQUIRED)
target_link_libraries(BulletFun PRIVATE raylib)