#include "grunt.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Grunt::Grunt(Player& player, Vector2 position) : Enemy(player, position)
{
    idleTexture = LoadTexture("Spritesheet/enemy/bardIdle.png");
    walkTexture = LoadTexture("Spritesheet/enemy/bardWalk.png");
    currentTexture = idleTexture;
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 150;
    health = maxHealth;
    movementSpeed = 20;
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