#pragma once
//#define RAYTMX_IMPLEMENTATION
#include "raytmx.h"
#include <vector>

class TerrainCollision
{
    public:
        TerrainCollision();
        //~TerrainCollision();
        void LoadMap(const char* tmx);
        void UnloadMap();
        void Draw();
        bool CheckCollisionPoly(const Rectangle& playerBoundingBox, TmxObject* polygon) const;
        bool CheckCollision(const Rectangle& playerBoundingBox) const;
        bool CheckCollisionTiles(const Rectangle& powerupSpawn, TmxObject* tile) const;
        Rectangle GetTerrainBounds() const;
        TmxMap* map;

    private:
        std::vector<Rectangle> collisionRectangles;
};