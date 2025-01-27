#include "archer.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Archer::Archer(Player& player, Vector2 position) : Enemy(player, position)
{
    std::cout << "Initializing Archer" << std::endl;
    enemyIdle = LoadTexture("Spritesheet/enemy/Idle.png");
    enemyWalk = LoadTexture("Spritesheet/enemy/Walk.png");
    currentTexture = enemyIdle;
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 70;
    health = maxHealth;
    movementSpeed = 20;
    std::cout << "Archer initialized" << std::endl;
}

void Archer::Update(float deltaTime)
{
    std::cout << "Updating Archer" << std::endl;
    Enemy::Update(deltaTime);
    //Move(deltaTime);
    std::cout << "Archer updated" << std::endl;
}

void Archer::Draw() const
{
    Enemy::Draw();
}

void Archer::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}