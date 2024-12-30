#include "enemy.h"
#include "player.h"
#include <iostream>
#include <raymath.h>

Enemy::Enemy(Player& player) : player(player), timeSinceLastAttack(0.0f), hitPlayer(false)
{
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 5;
    speedX = 2;
    speedY = 2;
    numFrames = 4;
    frameWidth = enemyIdle.width / numFrames;

    health = 100;
    
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
    }
    if (player.playerPosition.x < enemyPosition.x) {
        enemyPosition.x -= speedX;
        isMoving = true;
        direction = LEFT;
    }
    if (player.playerPosition.y > enemyPosition.y) {
        enemyPosition.y += speedY;
        isMoving = true;
    }
    if (player.playerPosition.y < enemyPosition.y) {
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

void Enemy::Attack(float deltaTime)
{
    timeSinceLastAttack += deltaTime;

    float distance = Vector2Distance(player.playerPosition, enemyPosition);
    if (distance < player.radius && timeSinceLastAttack > 1.0f) {
        player.healthPoints -= 10;
        health -= 10;
        timeSinceLastAttack = 0.0f;
        hitPlayer = true;
    } else {
        hitPlayer = false;
    }

    // if (health <= 0) {
    //     Destroy();
    // }
}

// bool Enemy::isDestroyed() const
// {
//     return health <= 0;
// }


void Enemy::Destroy()
{
    UnloadTexture(enemyIdle);
    UnloadTexture(enemyWalk);
}

void Enemy::Draw() const
{   
    if (direction == RIGHT) {
        DrawTextureRec(currentTexture, frameRec, enemyPosition, WHITE);
    } else {
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTextureRec(currentTexture, flippedFrameRec, enemyPosition, WHITE);
    }

    // Draw Health Bar above enemy
    float healthBarWidth = 40.0f;
    //float healthBarPercentage = (float)health / maxHealth;
    //float greenBarWidth = healthBarWidth * healthBarPercentage;

    // DrawRectangle(enemyPosition.x - 20, enemyPosition.y - 20, healthBarWidth, 5, RED);
    // for (int i = 0; i < player.healthPoints; i += 10) {
    //     if (hitPlayer) {
    //         player.healthPoints -= 10;
    //         DrawRectangle(enemyPosition.x - 20 + i, enemyPosition.y - 20, greenBarWidth, 5, GREEN);
    //     }
    // }

    for (int i = 0; i < health; i += 10) {
        DrawRectangleRec({ enemyPosition.x - 20 + i, enemyPosition.y - 20, 5, 5 }, RED);
        if (hitPlayer) {
            DrawRectangleRec({ enemyPosition.x - 20 + i, enemyPosition.y - 20, 5, 5 }, GREEN);
        }
    }
}