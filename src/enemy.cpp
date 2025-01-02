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
    maxHealth = 100;
    frameWidth = enemyIdle.width / numFrames;

    radius = 15;
    health = 100;
    
    enemyIdle = LoadTexture("src/Spritesheet/enemy/Idle.png");
    enemyWalk = LoadTexture("src/Spritesheet/enemy/Walk.png");

    frameRec = { 0.0f, 0.0f, (float)enemyIdle.width / numFrames, (float)enemyIdle.height };
    enemyPosition = { (float)GetScreenWidth() / 3, (float)GetScreenHeight() / 3 };
}

void Enemy::Update()
{
    frameRec.x = (float)currentFrame * (float)currentTexture.width / numFrames;

    // Check for bullet collisions with this enemy
    for (auto it = player.bullets.begin(); it != player.bullets.end(); ) {

        if (it->Collision(*this)) {
            std::cout << "Bullet collided with enemy!" << std::endl;
            // Handle collision (e.g., reduce enemy health, destroy bullet, etc.)

            health -= 10; // Example: reduce enemy health
            it = player.bullets.erase(it); // Remove the bullet
        } else {
            ++it;
        }
    }
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


void Enemy::Destroy()
{

    //UnloadTexture(enemyIdle);
    //UnloadTexture(enemyWalk);
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

    //float healthPercentage = (float)health / maxHealth;

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