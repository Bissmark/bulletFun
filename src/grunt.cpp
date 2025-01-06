#include "grunt.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Grunt::Grunt(Player& player, Vector2 position) : Enemy(player, position)
{
    idleTexture = LoadTexture("src/Spritesheet/enemy/bardIdle.png");
    walkTexture = LoadTexture("src/Spritesheet/enemy/bardWalk.png");
    currentTexture = idleTexture;
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 150;
    health = maxHealth;
}

void Grunt::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
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