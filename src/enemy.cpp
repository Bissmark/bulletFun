#include "enemy.h"

Enemy::Enemy()
    : x(100)
    , y(100)
    , speedX(5)
    , speedY(5)
    , radius(15)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    currentFrame = 0;

    framesCounter = 0;
    framesSpeed = 8;

    enemyIdle = LoadTexture("src/Spritesheet/enemy/walk.png");

    frameRec = { 0.0f, 0.0f, (float)enemyIdle.width / 6, (float)enemyIdle.height };
    enemyPosition = { (float)screenWidth / 3, (float)screenHeight / 3 };
}

void Enemy::Update()
{
    ++framesCounter;

    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > 5) currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)enemyIdle.width / 6;
    }
}

void Enemy::Draw() const
{
    DrawTextureRec(enemyIdle, frameRec, enemyPosition, WHITE);
}