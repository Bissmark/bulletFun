#pragma once
#include <raylib.h>

class Player;

class Enemy
{
    public: 
        Enemy(Player& player, Vector2 position);
        virtual ~Enemy() = default;
        Enemy(const Enemy&) = delete;              // Disallow copying
        Enemy& operator=(const Enemy&) = delete;   // Disallow assignment

        int radius;
        int health;
        Rectangle boxCollision;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() const;
        virtual void Attack(float deltaTime) = 0;

        void Move(float deltaTime);
        bool CheckCollisionWithOtherEnemy(const Enemy& other) const;
        bool Destroy();
        Rectangle GetBoundingBox() const;
        Vector2 enemyPosition;

    protected:
        Player& player;
        Texture2D enemyIdle;
        Texture2D enemyWalk;
        Rectangle frameRec;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        int speedX;
        int speedY;
        int numFrames;
        int maxHealth;
        int movementSpeed;
        float timeSinceLastAttack;
        float scale;
        bool hitPlayer;
        enum Direction { LEFT, RIGHT } direction;
        Texture2D currentTexture;
        void UpdateFrame();
};