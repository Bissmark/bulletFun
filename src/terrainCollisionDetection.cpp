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

bool TerrainCollision::CheckCollisionPoly(const Rectangle& playerBoundingBox, TmxObject* polygon) const {
    for (int i = 0; i < polygon->pointsLength; ++i) {
        int next = (i + 1) % polygon->pointsLength;
        if (CheckCollisionLines(
                { polygon->points[i].x, polygon->points[i].y },
                { polygon->points[next].x, polygon->points[next].y },
                { playerBoundingBox.x, playerBoundingBox.y },
                { playerBoundingBox.x + playerBoundingBox.width, playerBoundingBox.y + playerBoundingBox.height },
                nullptr)) {
            return true;
        }
    }
    return false;
}

bool TerrainCollision::CheckCollision(const Rectangle& playerBoundingBox) const
{
    if (map != nullptr) {
        if (map->layersLength > 1) {
            TmxLayer* collisionLayer = &map->layers[1];
            if (collisionLayer != nullptr) {
                if (collisionLayer->type == LAYER_TYPE_OBJECT_GROUP) {
                    for (uint32_t i = 0; i < collisionLayer->exact.objectGroup.objectsLength; ++i) {
                        TmxObject* object = &collisionLayer->exact.objectGroup.objects[i];
                        if (object->type == OBJECT_TYPE_POLYGON || object->type == OBJECT_TYPE_POLYLINE) {
                            for (int j = 0; j < object->pointsLength - 1; ++j) {
                                if(CheckCollisionPoly(playerBoundingBox, object)) {
                                    return true;
                                }
                            }
                        }
                    }
                } 
            } 
        } 
    }
    return false;
}