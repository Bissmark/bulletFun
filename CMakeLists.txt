cmake_minimum_required(VERSION 3.10)

project(BulletFun)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the directories
include_directories(${CMAKE_SOURCE_DIR}/include)

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
    src/background.cpp
    src/characterSelection.cpp
    src/auraDmg.cpp
    src/fireBreath.cpp
    src/rotatingBalls.cpp
    src/blizzard.cpp
    src/levelUp.cpp
    src/powerup.cpp
    src/skillBar.cpp
    src/skillPickup.cpp
    src/slash.cpp
    src/terrainCollisionDetection.cpp
    src/rlimGui.cpp
    src/imgui.cpp
    src/imgui_widgets.cpp
    src/imgui_draw.cpp
    src/imgui_tables.cpp
    src/imgui_demo.cpp
    src/inGameMenu.cpp
)

set_target_properties(BulletFun PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist")

# Include directories (for both native and Emscripten builds)
target_include_directories(BulletFun PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(BulletFun PRIVATE ${CMAKE_SOURCE_DIR}/include)

# If building for WebAssembly with Emscripten
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Disable timezone database for Emscripten
    add_definitions(-D_LIBCPP_HAS_NO_TIMEZONE -D_LIBCPP_DISABLE_TZDB)

    # Set output suffix to .html for web
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    # Set output directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist")

    # Emscripten-specific linker options
    set(EMSCRIPTEN_LINK_FLAGS
        "-sUSE_GLFW=3"
        "-sASSERTIONS=1"
        "-sWASM=1"
        "-sASYNCIFY"
        "-sGL_ENABLE_GET_PROC_ADDRESS=1"
        "-sEXPORTED_FUNCTIONS=[\"_main\"]"
        "-sEXPORTED_RUNTIME_METHODS=[\"ccall\",\"cwrap\"]"
        "-sFORCE_FILESYSTEM"
    )
    
    target_link_options(BulletFun PRIVATE ${EMSCRIPTEN_LINK_FLAGS} "--preload-file=${CMAKE_SOURCE_DIR}/Spritesheet@/Spritesheet")
    target_link_options(BulletFun PRIVATE ${EMSCRIPTEN_LINK_FLAGS} "--preload-file=${CMAKE_SOURCE_DIR}/Tileset@/Tileset")

    # Link Raylib for Emscripten
    set(RAYLIB_PATH "C:/Users/Gosh_/Desktop/Programming/Projects/C++/Raylib/BulletFun/lib" CACHE PATH "Path to Raylib Emscripten build")
    message(STATUS "Looking for Raylib in: ${RAYLIB_PATH}")
    file(GLOB RAYLIB_FILES "${RAYLIB_PATH}/*")
    message(STATUS "Files found in ${RAYLIB_PATH}: ${RAYLIB_FILES}")
    set(RAYLIB_LIB "${RAYLIB_PATH}/libraylib.a")
    if(NOT EXISTS "${RAYLIB_LIB}")
        message(FATAL_ERROR "Raylib library not found at ${RAYLIB_LIB}. Please ensure it exists.")
    endif()
    message(STATUS "RAYLIB_LIB set to: ${RAYLIB_LIB}")
    target_include_directories(BulletFun PRIVATE "C:/raylib/raylib/src")  # Adjust if headers are elsewhere
    target_link_libraries(BulletFun PRIVATE ${RAYLIB_LIB})
else()
    # Native build (e.g., Windows)
    set(RAYLIB_PATH "C:/raylib" CACHE PATH "Path to native Raylib build")
    find_library(RAYLIB_LIB raylib 
                 PATHS "${RAYLIB_PATH}/lib" 
                 NO_DEFAULT_PATH)
    if(NOT RAYLIB_LIB)
        message(FATAL_ERROR "Raylib library not found for native build at ${RAYLIB_PATH}/lib. Please ensure Raylib is installed there.")
    endif()
    target_include_directories(BulletFun PRIVATE "${RAYLIB_PATH}/include")
    target_link_libraries(BulletFun PRIVATE ${RAYLIB_LIB})
endif()

# Debug output
message(STATUS "Raylib library found at: ${RAYLIB_LIB}")