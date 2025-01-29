#define RAYTMX_IMPLEMENTATION
#include "raytmx.h"
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
        // if (map->layersLength > 1) {
        //     TmxLayer* collisionLayer = &map->layers[1];
        //     if (collisionLayer->type == LAYER_TYPE_OBJECT_GROUP) {
        //         for (uint32_t i = 0; i < collisionLayer->exact.objectGroup.objectsLength; ++i) {
        //             TmxObject* object = &collisionLayer->exact.objectGroup.objects[i];
        //             //std::cout << object->name << std::endl;
        //             if (object->type == OBJECT_TYPE_POLYGON || object->type == OBJECT_TYPE_POLYLINE) {
        //                 for (int j = 0; j < object->pointsLength - 1; ++j) {
        //                     DrawLine(object->points[j].x, object->points[j].y, object->points[j + 1].x, object->points[j + 1].y, GREEN);
        //                 }
        //                 // Draw line from last point to first point to close the polygon
        //                 DrawLine(object->points[object->pointsLength - 1].x, object->points[object->pointsLength - 1].y, object->points[0].x, object->points[0].y, GREEN);
        //             }

        //             if (object->type == OBJECT_TYPE_TILE) {
        //                 std::cout << object->x << " " << object->y << " " << object->width << " " << object->height << std::endl;
        //                 DrawRectangleLines(object->x, object->y - object->height, object->width, object->height, RED);
        //                 // Debug: Draw a small reference point at the tile's actual origin
        //                 DrawCircle(object->x, object->y, 3, BLUE);
        //             }
        //         }
        //     }
        // }
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

bool TerrainCollision::CheckCollisionTiles(const Rectangle& powerupSpawn, TmxObject* tile) const {
    if (map == nullptr) return false;

    // Adjust for correct positioning, just like in Draw()
    float tileX = tile->x;
    float tileY = tile->y - tile->height;  // Adjust since Tiled places objects at bottom-left

    // Create the tile's bounding box
    Rectangle tileRect = { tileX, tileY, tile->width, tile->height };

    // Check for intersection with powerup spawn area
    return CheckCollisionRecs(powerupSpawn, tileRect);
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
                            if(CheckCollisionPoly(playerBoundingBox, object) || CheckCollisionTiles(playerBoundingBox, object)) {
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


Rectangle TerrainCollision::GetTerrainBounds() const
{
    if (map != nullptr) {
        return { 0, 0, (float)map->width * map->tileWidth, (float)map->height * map->tileHeight };
    }
    return { 0, 0, 0, 0 };
}