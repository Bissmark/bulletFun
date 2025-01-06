#include "grunt.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Grunt::Grunt(Player& player) : Enemy(player)
{
    idleTexture = LoadTexture("src/Spritesheet/enemy/bardIdle.png");
    walkTexture = LoadTexture("src/Spritesheet/enemy/bardWalk.png");
    currentTexture = idleTexture;
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };
}

void Grunt::Update(float deltaTime)
{
    bool isMoving = false;

    // Update position and check if the enemy is moving
    if (player.playerPosition.x > enemyPosition.x) {
        enemyPosition.x += speedX * deltaTime;
        isMoving = true;
        direction = RIGHT;
    }
    if (player.playerPosition.x < enemyPosition.x) {
        enemyPosition.x -= speedX * deltaTime;
        isMoving = true;
        direction = LEFT;
    }
    if (player.playerPosition.y > enemyPosition.y) {
        enemyPosition.y += speedY * deltaTime;
        isMoving = true;
    }
    if (player.playerPosition.y < enemyPosition.y) {
        enemyPosition.y -= speedY * deltaTime;
        isMoving = true;
    }

    // Switch between idle and walk animations
    if (isMoving) {
        if (currentTexture.id != walkTexture.id) {
            currentTexture = walkTexture;
            numFrames = 6; // Assuming walk animation has 6 frames
            frameWidth = currentTexture.width / numFrames;
        }
    } else {
        if (currentTexture.id != idleTexture.id) {
            currentTexture = idleTexture;
            numFrames = 4; // Assuming idle animation has 4 frames
            frameWidth = currentTexture.width / numFrames;
        }
    }

    // Update the frame rectangle for animation
    frameRec.x = (float)currentFrame * frameWidth;
    frameRec.width = (float)frameWidth;
    frameRec.height = (float)currentTexture.height;

    Enemy::Update(deltaTime);

    UpdateFrame();
}

void Grunt::Draw() const
{
    if (direction == RIGHT) {
        DrawTextureRec(currentTexture, frameRec, enemyPosition, WHITE);
    } else {
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTextureRec(currentTexture, flippedFrameRec, enemyPosition, WHITE);
    }

    // Draw health bar
    float healthPercentage = (float)health / maxHealth;
    float barWidth = 50.0f; // Width of the health bar
    float barHeight = 5.0f; // Height of the health bar
    Vector2 barPosition = { enemyPosition.x, enemyPosition.y - 10.0f }; // Position of the health bar above the enemy

    // Draw the background of the health bar (max health)
    DrawRectangle(barPosition.x, barPosition.y, barWidth, barHeight, RED);

    // Draw the current health bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth * healthPercentage, barHeight, GREEN);
}

void Grunt::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}