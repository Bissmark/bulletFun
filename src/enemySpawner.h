#pragma once
#include <vector>
#include <memory>
#include "enemy.h"
#include "player.h"

class Player;

class EnemySpawner
{
    public:
        EnemySpawner(Player& player, int maxEnemies, int spawnRate);
        void Update(float deltaTime);
        void Draw() const;
        void SpawnEnemy();
        void DestroyEnemy();
        Player& player;

    private:
        std::vector<std::unique_ptr<Enemy>> enemies;
        int maxEnemies;
        int spawnRate;
        int currentEnemies;
        int framesCounter;
        float spawnCounter;
};