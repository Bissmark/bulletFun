#pragma once
#include <raylib.h>
#include "player.h"

class Enemy
{
    public: 
        Enemy(Player& player);
        void Update();
        void Move();
        void Draw() const;
        void Attack(float deltaTime);
        void Destroy();

    private:
        Player& player;
        Vector2 enemyPosition;
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
        int radius;
        int numFrames;
        float timeSinceLastAttack;
        bool hitPlayer;
        int health;
        enum Direction { LEFT, RIGHT } direction;
        void UpdateFrame();
};