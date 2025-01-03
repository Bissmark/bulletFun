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
        enemy.Move();
        enemy.Update();
        enemy.Attack(deltaTime);
    }

    // Update the current number of enemies
    currentEnemies = enemies.size();
}

void EnemySpawner::Draw() const
{
    for (const auto& enemy : enemies) {
        enemy.Draw();
    }
}

void EnemySpawner::SpawnEnemy()
{
    enemies.emplace_back(player);
    ++currentEnemies;
}

void EnemySpawner::DestroyEnemy()
{
    if (!enemies.empty()) {
        enemies.pop_back();
        --currentEnemies;
    }
}