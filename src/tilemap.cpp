#include "tilemap.h"
#include <raymath.h>
#include <cstdlib>
#include <unordered_map>

Tilemap::Tilemap(int chunkSize, int tileSize)
    : chunkSize(chunkSize), tileSize(tileSize)
{
}

Tilemap::~Tilemap()
{
    Unload();
}

void Tilemap::Generate(int level)
{
    LoadTextures(level);
    chunks.clear();
}

void Tilemap::LoadTextures(int level)
{
    // Load different textures based on the level
    switch (level) {
        case 1:
            floorTexture = LoadTexture("Spritesheet/floor1.png");
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

void Tilemap::LoadChunk(int chunkX, int chunkY)
{
    Vector2 chunkPos = { (float)chunkX, (float)chunkY };
    if (chunks.find(chunkPos) != chunks.end()) return;

    Chunk chunk;
    for (int y = 0; y < chunkSize; ++y) {
        for (int x = 0; x < chunkSize; ++x) {
            Tile tile;
            tile.position = { (float)(chunkX * chunkSize + x) * tileSize, (float)(chunkY * chunkSize + y) * tileSize };
            tile.texture = floorTexture;
            tile.isWalkable = true;
            chunk.tiles.push_back(tile);
        }
    }
    chunks[chunkPos] = chunk;
}

void Tilemap::UnloadChunk(int chunkX, int chunkY)
{
    Vector2 chunkPos = { (float)chunkX, (float)chunkY };
    chunks.erase(chunkPos);
}

Vector2 Tilemap::GetCenterPosition() const
{
    return { (float)(chunkSize * tileSize) / 2, (float)(chunkSize * tileSize) / 2 };
}

void Tilemap::Draw(const Vector2& playerPosition) const
{
    int playerChunkX = (int)(playerPosition.x / (chunkSize * tileSize));
    int playerChunkY = (int)(playerPosition.y / (chunkSize * tileSize));

    for (int y = -1; y <= 1; ++y) {
        for (int x = -1; x <= 1; ++x) {
            int chunkX = playerChunkX + x;
            int chunkY = playerChunkY + y;
            Vector2 chunkPos = { (float)chunkX, (float)chunkY };
            if (chunks.find(chunkPos) == chunks.end()) {
                const_cast<Tilemap*>(this)->LoadChunk(chunkX, chunkY);
            }
            const Chunk& chunk = chunks.at(chunkPos);
            for (const auto& tile : chunk.tiles) {
                DrawTexture(tile.texture, tile.position.x, tile.position.y, WHITE);
            }
        }
    }
}

void Tilemap::Unload()
{
    UnloadTexture(floorTexture);
    UnloadTexture(wallTexture);
    chunks.clear();
}