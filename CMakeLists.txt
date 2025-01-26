cmake_minimum_required(VERSION 3.10)
project(BulletFun)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (EMSCRIPTEN)
    set(PLATFORM Web CACHE INTERNAL "")
    list(APPEND CMAKE_EXE_LINKER_FLAGS "-s USE_GLFW=3 -sASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

include(FetchContent)

set(RAYLIB_VERSION 5)

# Add the executable
add_executable(${PROJECT_NAME}
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
    src/terrainCollisionDetection.cpp
    src/rlimGui.cpp
    src/imgui.cpp
    src/imgui_widgets.cpp
    src/imgui_draw.cpp
    src/imgui_tables.cpp
    src/imgui_demo.cpp
)


# add_library(raylib-tmx-h INTERFACE)

# Include Directory
# target_include_directories(raylib-tmx-h INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/)

# Include directories
target_include_directories(BulletFun PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(BulletFun PRIVATE ${CMAKE_SOURCE_DIR}/include)


# Link Raylib
set(CMAKE_PREFIX_PATH "C:/raylib")
# find_package(raylib REQUIRED)
target_link_libraries(BulletFun PRIVATE raylib)