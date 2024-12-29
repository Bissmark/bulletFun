#include "enemySpawner.h"
#include "player.h"
#include <raymath.h>

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

    if (framesCounter >= 60) {
        framesCounter = 0;
        //CheckCollision();
    }

    if (spawnCounter >= spawnRate && currentEnemies < maxEnemies) {
        spawnCounter = 0.0f;
        SpawnEnemy();
    }

    for (auto& enemy : enemies) {
        enemy.Move();
        enemy.Update();
        enemy.Attack(deltaTime);
    }
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
    enemies.back().Draw();
    ++currentEnemies;
}

void EnemySpawner::DestroyEnemy()
{
    if (!enemies.empty()) {
        enemies.pop_back();
        --currentEnemies;
    }
}

// void EnemySpawner::CheckCollision()
// {
//     CheckPlayerCollision();
//     CheckBulletCollision();
// }

// void EnemySpawner::CheckPlayerCollision()
// {
//     for (auto& enemy : enemies) {
//         float distance = Vector2Distance(enemy.enemyPosition, enemy.player.playerPosition);
//         if (distance < enemy.radius + enemy.player.radius) {
//             enemy.player.healthPoints -= 10;
//         }
//     }
// }

// void EnemySpawner::CheckBulletCollision()
// {
//     for (auto& enemy : enemies) {
//         for (auto& bullet : enemy.bullets) {
//             float distance = Vector2Distance(bullet.bulletPosition, enemy.enemyPosition);
//             if (distance < bullet.radius + enemy.radius) {
//                 bullet.isAlive = false;
//                 enemy.healthPoints -= 10;
//             }
//         }
//     }
// }