#pragma once
#include <raylib.h>

class Player;
class Bullet;

class Enemy
{
    public: 
        Enemy(Player& player);
        Vector2 enemyPosition;
        int radius;
        int health;
        void Update();
        void Move();
        void Draw() const;
        void Attack(float deltaTime);
        void Destroy();

    private:
        Player& player;
        Texture2D enemyIdle;
        Texture2D enemyWalk;
        Texture2D currentTexture;
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
};