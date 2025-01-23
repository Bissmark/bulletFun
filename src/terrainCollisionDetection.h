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
        bool CheckCollision(const Vector2& playerPosition) const;
        Vector2 GetCenterPosition() const;

    private:
        TmxMap* map;

};