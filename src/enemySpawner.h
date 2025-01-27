#pragma once
#include <vector>
#include <memory>
#include <array>
#include "enemy.h"

class Player;

class EnemySpawner
{
    public:
        EnemySpawner(Player& player, int spawnRate);
        void Update(float deltaTime);
        void Draw() const;
        void SpawnEnemy();
        void DestroyEnemy();
        std::vector<std::unique_ptr<Enemy>> enemies;

    private:
        Player& player;
        int maxEnemies;
        int spawnRate;
        int currentEnemies;
        int framesCounter;
        int amountOfEnemyTypes;
        float spawnCounter;

        enum EnemyType { ARCHER, SLIME, GRUNT };
        std::unique_ptr<Enemy> CreateEnemy(EnemyType type, Vector2 position);
};