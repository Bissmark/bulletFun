#include "enemySpawner.h"
#include "player.h"
#include "archer.h"
#include "grunt.h"
#include "slime.h"
#include <raymath.h>
#include <algorithm>
#include <iostream>

EnemySpawner::EnemySpawner(Player& player, int spawnRate, TerrainCollision& tileCollision)
    : player(player)
    , maxEnemies(10)
    , spawnRate(spawnRate)
    , currentEnemies(0)
    , framesCounter(0)
    , spawnCounter(0.0f)
    , amountOfEnemyTypes(3)
    , tileCollision(tileCollision)
{
}

void EnemySpawner::Update(float deltaTime)
{
    ++framesCounter;
    spawnCounter += deltaTime;

    maxEnemies = std::max(10, player.level * 2);
    
    if (spawnCounter >= spawnRate && currentEnemies < maxEnemies) {
        spawnCounter = 0.0f;
        SpawnEnemy();
    }

    for (auto& enemy : enemies) {
        enemy->Update(deltaTime);
    }

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        (*it)->Update(deltaTime); // Call the enemy's update method

         // Check for bullet collisions with this enemy
        for (auto bulletIt = player.bullets.begin(); bulletIt != player.bullets.end(); ) {
            if (bulletIt->Collision(**it)) {
                bulletIt = player.bullets.erase(bulletIt); // Remove the bullet
            } else {
                ++bulletIt;
            }
        }

        for (auto& otherEnemy : enemies) {
            if (otherEnemy.get() != it->get() && (*it)->CheckCollisionWithOtherEnemy(*otherEnemy)) {
                // Adjust position to avoid stacking
                Vector2 direction = Vector2Subtract((*it)->enemyPosition, otherEnemy->enemyPosition);
                direction = Vector2Normalize(direction);
                (*it)->enemyPosition.x += direction.x * 10.0f * deltaTime;
                (*it)->enemyPosition.y += direction.y * 10.0f * deltaTime;
            }
        }
        
        if ((*it)->Destroy()) {
            it = enemies.erase(it);
        } else {
            ++it; // Move to the next enemy
        }
    }
    // Update the current number of enemies
    currentEnemies = enemies.size();
}

void EnemySpawner::Draw() const
{
    for (const auto& enemy : enemies) {
        enemy->Draw();
    }
}

void EnemySpawner::SpawnEnemy()
{
    EnemyType type = static_cast<EnemyType>(GetRandomValue(0, amountOfEnemyTypes - 1));

    bool validPosition = false;
    Vector2 position;
    Rectangle enemyBounds;

    Rectangle terrainBounds = tileCollision.GetTerrainBounds(); // Get the map bounds

    while (!validPosition) 
    {
        // Pick a random position within terrain bounds
        position.x = (float)GetRandomValue(terrainBounds.x, terrainBounds.x + terrainBounds.width);
        position.y = (float)GetRandomValue(terrainBounds.y, terrainBounds.y + terrainBounds.height);
        
        // Create a bounding box for collision checking
        enemyBounds = { position.x, position.y, 32, 32 }; // Adjust size based on enemy size

        // Check if this position collides with walls
        if (!tileCollision.CheckCollision(enemyBounds)) 
        {
            bool tileCollisionDetected = false;
            
            // Iterate over tile objects in collision layer
            if (tileCollision.map != nullptr && tileCollision.map->layersLength > 1) 
            {
                TmxLayer* collisionLayer = &tileCollision.map->layers[1]; // Assuming layer 1 is the collision layer
                if (collisionLayer->type == LAYER_TYPE_OBJECT_GROUP) 
                {
                    for (uint32_t i = 0; i < collisionLayer->exact.objectGroup.objectsLength; ++i) 
                    {
                        TmxObject* object = &collisionLayer->exact.objectGroup.objects[i];
                        if (object->type == OBJECT_TYPE_TILE) 
                        {
                            if (tileCollision.CheckCollisionTiles(enemyBounds, object)) 
                            {
                                tileCollisionDetected = true;
                                break;
                            }
                        }
                    }
                }
            }

            // If no tile collision, accept this position
            if (!tileCollisionDetected) 
            {
                validPosition = true;
            }
        }
    }

    // Spawn enemy at the valid position
    enemies.emplace_back(CreateEnemy(type, position));
    ++currentEnemies;
}


void EnemySpawner::DestroyEnemy()
{
    if (!enemies.empty()) {
        enemies.pop_back();
    }
}

std::unique_ptr<Enemy> EnemySpawner::CreateEnemy(EnemyType type, Vector2 position)
{
    switch (type) {
        case ARCHER:
            return std::make_unique<Archer>(player, position, tileCollision);
        case SLIME:
            return std::make_unique<Slime>(player, position, tileCollision);
        case GRUNT:
            return std::make_unique<Grunt>(player, position, tileCollision);
        default:
            return nullptr;
    }
}