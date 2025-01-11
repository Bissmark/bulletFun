#include "tilemap.h"
#include <raymath.h>
#include <cstdlib>

Tilemap::Tilemap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize)
{
}

Tilemap::~Tilemap()
{
    Unload();
}

void Tilemap::Generate(int level)
{
    LoadTextures(level);

    tiles.clear();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tile tile;
            tile.position = { (float)x * tileSize, (float)y * tileSize };
            // if (rand() % 10 < 2) { // 20% chance to be a wall
            //     tile.texture = wallTexture;
            //     tile.isWalkable = false;
            // } else {
                 tile.texture = floorTexture;
                 tile.isWalkable = true;
            // }
            tiles.push_back(tile);
        }
    }
}

void Tilemap::LoadTextures(int level)
{
    // Load different textures based on the level
    switch (level) {
        case 1:
            floorTexture = LoadTexture("src/Spritesheet/floor1.png");
            //wallTexture = LoadTexture("src/Textures/wall1.png");
            break;
        case 2:
            floorTexture = LoadTexture("src/Textures/floor2.png");
            wallTexture = LoadTexture("src/Textures/wall2.png");
            break;
        // Add more cases for additional levels
        default:
            floorTexture = LoadTexture("src/Textures/floor1.png");
            wallTexture = LoadTexture("src/Textures/wall1.png");
            break;
    }
}

Vector2 Tilemap::GetCenterPosition() const
{
    return { (float)(width * tileSize) / 2, (float)(height * tileSize) / 2 };
}

void Tilemap::Draw() const
{
    for (const auto& tile : tiles) {
        DrawTexture(tile.texture, tile.position.x, tile.position.y, WHITE);
    }
}

void Tilemap::Unload()
{
    UnloadTexture(floorTexture);
    UnloadTexture(wallTexture);
}