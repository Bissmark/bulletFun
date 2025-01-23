#pragma once
#include "include/raytmx.h"

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
        Vector2 GetCenterPosition() const;

    private:
        TmxMap* map;

};