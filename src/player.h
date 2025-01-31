#pragma once
#include <raylib.h>
#include <vector>
#include <memory>
#include "bullet.h"
#include "slash.h"
#include "abilityManager.h"
#include "ability.h"

class Player
{
    public: 
        enum class PlayerType { WARRIOR, MAGE, ARCHER };
        Player();
        void Update(std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime);
        void Move();
        void Draw(const Camera2D& camera) const;
        void Fire(const Camera2D& camera);
        void AutoAttack(std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime);
        void PlayerLevelUp();
        void DrawExp() const;
        void AddAbility(std::unique_ptr<Ability> ability);
        Rectangle GetBoundingBox() const;

        Vector2 playerPosition;
        int radius;
        int healthPoints;
        int maxHealth;
        int experiencePoints;
        int maxExperiencePoints;
        int level;
        int attackSpeed;
        double elapsedTime;
        bool gamePaused;
        int critChance;
        int critDamage;
        int baseDamage;
        int cooldownReduction;
        std::vector<Bullet> bullets;
        PlayerType playerType;
        Rectangle frameRec;
        Texture2D currentTexture;
        unsigned int numFrames;
        bool leveledUp;
        bool leveledUpWindowActive;
        float scale;
        int enemiesKilled;

    private:
        Texture2D playerIdle;
        Texture2D playerWalk;
        int speedX;
        int speedY;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        int currentEnemiesKilled;
        enum Direction { LEFT, RIGHT } direction;
        double startTime;
        void UpdateFrame();
        Enemy* FindClosestEnemy(std::vector<std::unique_ptr<Enemy>>& enemies);
        AbilityManager abilityManager;
};