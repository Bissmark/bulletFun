#include "grunt.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Grunt::Grunt(Player& player, Vector2 position, TerrainCollision& tileCollision) : Enemy(player, position, tileCollision)
{
    enemyIdle = LoadTexture("Spritesheet/enemy/bardIdle.png");
    enemyWalk = LoadTexture("Spritesheet/enemy/bardWalk.png");
    currentTexture = enemyIdle;
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 150;
    health = maxHealth;
    movementSpeed = 10;
}

void Grunt::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
}

void Grunt::Draw() const
{
    Enemy::Draw();
}

void Grunt::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}