#pragma once
#include <vector>
#include "enemy.h"
#include "player.h"

class EnemySpawner
{
    public:
        EnemySpawner(Player& player, int maxEnemies, int spawnRate);
        void Update(float deltaTime);
        void Draw() const;
        void SpawnEnemy();
        void DestroyEnemy();
        void CheckCollision();

    private:
        Player& player;
        std::vector<Enemy> enemies;
        int maxEnemies;
        int spawnRate;
        int currentEnemies;
        int framesCounter;
        float spawnCounter;
};