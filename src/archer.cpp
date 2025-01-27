#include "archer.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Archer::Archer(Player& player, Vector2 position) : Enemy(player, position)
{
    idleTexture = LoadTexture("Spritesheet/enemy/Idle.png");
    walkTexture = LoadTexture("Spritesheet/enemy/Walk.png");
    currentTexture = idleTexture;
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 70;
    health = maxHealth;
    movementSpeed = 20;
}

void Archer::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
}

void Archer::Draw() const
{
    Enemy::Draw();
}

void Archer::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}