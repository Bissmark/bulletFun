#pragma once
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include "vector2_hash.h"

struct Tile {
    Vector2 position;
    Texture2D texture;
    bool isWalkable;
};

struct Chunk {
    std::vector<Tile> tiles;
};

class Tilemap {
public:
    Tilemap(int chunkSize, int tileSize);
    ~Tilemap();
    void Generate(int level);
    void Draw(const Vector2& playerPosition) const;
    void Unload();
    Vector2 GetCenterPosition() const;

private:
    int chunkSize;
    int tileSize;
    std::unordered_map<Vector2, Chunk, Vector2Hash> chunks;
    Texture2D floorTexture;
    Texture2D wallTexture;
    void LoadTextures(int level);
    void LoadChunk(int chunkX, int chunkY);
    void UnloadChunk(int chunkX, int chunkY);
};