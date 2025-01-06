#pragma once
#include <vector>
#include <memory>
#include "enemy.h"

class Player;

class EnemySpawner
{
    public:
        EnemySpawner(Player& player, int maxEnemies, int spawnRate);
        void Update(float deltaTime);
        void Draw() const;
        void SpawnEnemy();
        void DestroyEnemy();

    private:
        Player& player;
        std::vector<std::unique_ptr<Enemy>> enemies;
        int maxEnemies;
        int spawnRate;
        int currentEnemies;
        int framesCounter;
        float spawnCounter;

        enum EnemyType { ARCHER, SLIME, MAGE, WARRIOR, GRUNT };
        std::unique_ptr<Enemy> CreateEnemy(EnemyType type, Vector2 position);
};