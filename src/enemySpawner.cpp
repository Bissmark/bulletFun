#include "enemySpawner.h"
#include "player.h"
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
        enemy->Update();
        enemy->Attack(deltaTime);
    }

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        (*it)->Update(); // Call the enemy's update method
        
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
    enemies.emplace_back(std::make_unique<Enemy>(player));
    ++currentEnemies;
}

void EnemySpawner::DestroyEnemy()
{
    if (!enemies.empty()) {
        enemies.pop_back();
    }
}