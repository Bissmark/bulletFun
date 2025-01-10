#pragma once
#include <raylib.h>
#include <vector>
#include <memory>
#include "bullet.h"
#include "slash.h"

class Player
{
    public: 
        enum class PlayerType { WARRIOR, MAGE, ARCHER };
        Player();
        Vector2 playerPosition;
        int radius;
        int healthPoints;
        int experiencePoints;
        int maxExperiencePoints;
        int level;
        int attackSpeed;
        double elapsedTime;
        bool gamePaused;
        void Update();
        void Move();
        void Draw() const;
        void Fire(const Camera2D& camera);
        void AutoAttack(std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime);
        void LevelUp();
        void DrawExp() const;
        void DrawLevelUpBox();
        float critChance;
        float critDamage;
        int baseDamage;
        std::vector<Bullet> bullets;
        PlayerType playerType;

    private:
        Texture2D playerIdle;
        Texture2D playerWalk;
        Texture2D currentTexture;
        Rectangle frameRec;
        Rectangle boxCollision;
        int speedX;
        int speedY;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        int currentEnemiesKilled;
        unsigned int numFrames;
        bool leveledUp;
        enum Direction { LEFT, RIGHT } direction;
        double startTime;
        void UpdateFrame();
        Enemy* FindClosestEnemy(std::vector<std::unique_ptr<Enemy>>& enemies);
};