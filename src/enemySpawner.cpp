#include "enemySpawner.h"
#include "player.h"
#include "archer.h"
#include "grunt.h"
#include "slime.h"
#include <raymath.h>
#include <algorithm>

EnemySpawner::EnemySpawner(Player& player, int maxEnemies, int spawnRate)
    : player(player)
    , maxEnemies(maxEnemies)
    , spawnRate(spawnRate)
    , currentEnemies(0)
    , framesCounter(0)
    , spawnCounter(0.0f)
{
}

void EnemySpawner::Update(float deltaTime)
{
    ++framesCounter;
    spawnCounter += deltaTime;

    if (spawnCounter >= spawnRate && currentEnemies < maxEnemies) {
        spawnCounter = 0.0f;
        SpawnEnemy();
    }

    for (auto& enemy : enemies) {
        enemy->Move();
        enemy->Update(deltaTime);
        enemy->Attack(deltaTime);
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
        
        if ((*it)->Destroy()) { // Check if the enemy should be destroyed
            it = enemies.erase(it); // Remove the enemy from the vector
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
    EnemyType type = static_cast<EnemyType>(GetRandomValue(0, 3));
    enemies.emplace_back(CreateEnemy(type));
    ++currentEnemies;
}

void EnemySpawner::DestroyEnemy()
{
    if (!enemies.empty()) {
        enemies.pop_back();
    }
}

std::unique_ptr<Enemy> EnemySpawner::CreateEnemy(EnemyType type)
{
    switch (type) {
        case ARCHER:
            return std::make_unique<Archer>(player);
        case SLIME:
            return std::make_unique<Slime>(player);
        case MAGE:
            //return std::make_unique<Mage>(player);
        case WARRIOR:
            //return std::make_unique<Warrior>(player);
        case GRUNT:
            return std::make_unique<Grunt>(player);
        default:
            return nullptr;
    }
}