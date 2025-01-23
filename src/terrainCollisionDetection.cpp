#include "terrainCollisionDetection.h"
#include <iostream>

TerrainCollision::TerrainCollision() : map(nullptr)
{
}

// TerrainCollision::~TerrainCollision()
// {
//     UnloadMap();
// }

void TerrainCollision::LoadMap(const char* tmx)
{
    map = LoadTMX(tmx);
}

void TerrainCollision::UnloadMap()
{
    if (map != nullptr) {
        UnloadTMX(map);
        map = nullptr;
    }
}

void TerrainCollision::Draw()
{
    if (map != nullptr) {
        DrawTMX(map, nullptr, 0, 0, WHITE);

        // Draw debug lines around the collision objects
        if (map->layersLength > 1) {
            TmxLayer* collisionLayer = &map->layers[1];
            if (collisionLayer->type == LAYER_TYPE_OBJECT_GROUP) {
                for (uint32_t i = 0; i < collisionLayer->exact.objectGroup.objectsLength; ++i) {
                    TmxObject* object = &collisionLayer->exact.objectGroup.objects[i];
                    if (object->type == OBJECT_TYPE_POLYGON || object->type == OBJECT_TYPE_POLYLINE) {
                        for (int j = 0; j < object->pointsLength - 1; ++j) {
                            DrawLine(object->points[j].x, object->points[j].y, object->points[j + 1].x, object->points[j + 1].y, GREEN);
                        }
                        // Draw line from last point to first point to close the polygon
                        DrawLine(object->points[object->pointsLength - 1].x, object->points[object->pointsLength - 1].y, object->points[0].x, object->points[0].y, GREEN);
                    }
                }
            }
        }
    }
}

bool TerrainCollision::CheckCollision(const Vector2& playerPosition) const
{
    if (map != nullptr) {
        if (map->layersLength > 1) {
            TmxLayer* collisionLayer = &map->layers[1];
            if (collisionLayer != nullptr) {
                if (collisionLayer->type == LAYER_TYPE_OBJECT_GROUP) {
                    for (uint32_t i = 0; i < collisionLayer->exact.objectGroup.objectsLength; ++i) {
                        TmxObject* object = &collisionLayer->exact.objectGroup.objects[i];
                        if (object->type == OBJECT_TYPE_POLYGON || object->type == OBJECT_TYPE_POLYLINE) {
                            if (CheckCollisionPointPoly(playerPosition, object->points, object->pointsLength)) {
                                return true;
                            }
                        }
                    }
                } 
            } 
        } 
    }
    return false;
}

Vector2 TerrainCollision::GetCenterPosition() const
{
    if (map != nullptr) {
        return { map->width * map->tileWidth / 2, map->height * map->tileHeight / 2 };
    }
    return { 0, 0 };
}