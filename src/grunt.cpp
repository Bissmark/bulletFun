#include "grunt.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Grunt::Grunt(Player& player, Vector2 position) : Enemy(player, position)
{
    std::cout << "Initializing Grunt" << std::endl;
    enemyIdle = LoadTexture("Spritesheet/enemy/bardIdle.png");
    if (idleTexture.id == 0) {
        std::cerr << "Failed to load texture: Spritesheet/enemy/bardIdle.png" << std::endl;
    }
    enemyWalk = LoadTexture("Spritesheet/enemy/bardWalk.png");
    if (walkTexture.id == 0) {
        std::cerr << "Failed to load texture: Spritesheet/enemy/bardWalk.png" << std::endl;
    }
    currentTexture = enemyIdle;
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 150;
    health = maxHealth;
    movementSpeed = 10;
    std::cout << "Grunt initialized" << std::endl;
}

void Grunt::Update(float deltaTime)
{
    std::cout << "Updating Grunt" << std::endl;
    Enemy::Update(deltaTime);
    std::cout << "Grunt updated" << std::endl;
}

void Grunt::Draw() const
{
    std::cout << "Drawing Grunt" << std::endl;
    Enemy::Draw();
    std::cout << "Finished drawing Grunt" << std::endl;
}

void Grunt::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}