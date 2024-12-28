#include "enemy.h"
#include "player.h"
#include <iostream>

Enemy::Enemy(Player& player) : player(player)
{
    currentFrame = 0;

    framesCounter = 0;
    framesSpeed = 5;

    speedX = 2;
    speedY = 2;

    numFrames = 4;
    frameWidth = enemyIdle.width / numFrames;
    
    enemyIdle = LoadTexture("src/Spritesheet/enemy/Idle.png");
    enemyWalk = LoadTexture("src/Spritesheet/enemy/Walk.png");

    frameRec = { 0.0f, 0.0f, (float)enemyIdle.width / numFrames, (float)enemyIdle.height };
    enemyPosition = { (float)GetScreenWidth() / 3, (float)GetScreenHeight() / 3 };
}

void Enemy::Update()
{
    frameRec.x = (float)currentFrame * (float)currentTexture.width / numFrames;
}

void Enemy::Move()
{
    bool isMoving = false;

    if (player.playerPosition.x > enemyPosition.x) {
        enemyPosition.x += speedX;
        isMoving = true;
        direction = RIGHT;
    } else if (player.playerPosition.x < enemyPosition.x) {
        enemyPosition.x -= speedX;
        isMoving = true;
        direction = LEFT;
    } else if (player.playerPosition.y > enemyPosition.y) {
        enemyPosition.y += speedY;
        isMoving = true;
    } else if (player.playerPosition.y < enemyPosition.y) {
        enemyPosition.y -= speedY;
        isMoving = true;
    }

    if (isMoving) {
        if (currentTexture.id != enemyWalk.id) {
            currentTexture = enemyWalk;
            numFrames = 6;
            frameWidth = enemyWalk.width / numFrames;
        }
    } else {
        if (currentTexture.id != enemyIdle.id) {
            currentTexture = enemyIdle;
            numFrames = 4;
            frameWidth = enemyIdle.width / numFrames;
        }
    }

    UpdateFrame();
}

void Enemy::UpdateFrame()
{
    ++framesCounter;

    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        ++currentFrame;
        currentFrame %= numFrames;
        frameRec.x = (float)frameWidth * currentFrame;
    }
}

void Enemy::Draw() const
{   if (direction == RIGHT) {
        DrawTextureRec(enemyIdle, frameRec, enemyPosition, WHITE);
    } else {
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTextureRec(currentTexture, flippedFrameRec, enemyPosition, WHITE);
    }
}