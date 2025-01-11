#pragma once
#include <raylib.h>
#include <vector>

struct Tile {
    Vector2 position;
    Texture2D texture;
    bool isWalkable;
};

class Tilemap {
public:
    Tilemap(int width, int height, int tileSize);
    ~Tilemap();
    void Generate(int level);
    void Draw() const;
    void Unload();
    Vector2 GetCenterPosition() const;

private:
    int width;
    int height;
    int tileSize;
    std::vector<Tile> tiles;
    Texture2D floorTexture;
    Texture2D wallTexture;
    void LoadTextures(int level);
};