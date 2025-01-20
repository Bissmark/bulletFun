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
    src/abilityManager.cpp
    src/auraDmg.cpp
    src/background.cpp
    src/characterSelection.cpp
    src/flamethrower.cpp
    src/levelUp.cpp
    src/powerup.cpp
    src/skillBar.cpp
    src/skillPickup.cpp
    src/slash.cpp
    src/tilemap.cpp
    # Add other source files here
)

file(COPY ${CMAKE_SOURCE_DIR}/src/Spritesheet DESTINATION ${CMAKE_BINARY_DIR})


# Include directories
target_include_directories(BulletFun PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link Raylib
set(CMAKE_PREFIX_PATH "C:/raylib")
# find_package(raylib REQUIRED)
target_link_libraries(BulletFun PRIVATE raylib)