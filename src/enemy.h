#pragma once
#include <raylib.h>

class Player;
class Bullet;

class Enemy
{
    public: 
        Enemy(Player& player);
        virtual ~Enemy() = default;
        Enemy(const Enemy&) = delete;              // Disallow copying
        Enemy& operator=(const Enemy&) = delete;   // Disallow assignment
        Vector2 enemyPosition;
        int radius;
        int health;
        Rectangle boxCollision;
        virtual void Update(float deltaTime) = 0;
        void Move();
        virtual void Draw() const;
        virtual void Attack(float deltaTime) = 0;
        bool Destroy();

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
        float timeSinceLastAttack;
        bool hitPlayer;
        enum Direction { LEFT, RIGHT } direction;
        void UpdateFrame();

    private:
        Texture2D currentTexture;

};