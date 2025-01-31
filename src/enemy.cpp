#include "enemy.h"
#include "player.h"
#include <iostream>
#include <raymath.h>

Enemy::Enemy(Player& player, Vector2 position, TerrainCollision& tileCollision) : 
    player(player), 
    enemyPosition(position),
    timeSinceLastAttack(0.0f), 
    hitPlayer(false), 
    scale(0.5f),
    tileCollision(tileCollision)
{
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 5;
    numFrames = 4;
    frameWidth = enemyIdle.width / numFrames;

    enemyIdle = LoadTexture("Spritesheet/enemy/Idle.png");
    currentTexture = enemyIdle;

    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };
    boxCollision = { enemyPosition.x, enemyPosition.y, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 100;
    radius = 15;
    health = 100;
}

void Enemy::Update(float deltaTime)
{
    Move(deltaTime);
    Attack(deltaTime);

    frameRec.x = (float)currentFrame * (float)currentTexture.width / numFrames;
}

void Enemy::Move(float deltaTime)
{
    bool isMoving = false;
    Vector2 oldPosition = enemyPosition;

    // Move towards player
    Vector2 directionToPlayer = Vector2Subtract(player.playerPosition, enemyPosition);
    directionToPlayer = Vector2Normalize(directionToPlayer);
    
    enemyPosition.x += directionToPlayer.x * movementSpeed * deltaTime;
    enemyPosition.y += directionToPlayer.y * movementSpeed * deltaTime;
    
    boxCollision.x = enemyPosition.x;
    boxCollision.y = enemyPosition.y;

    // Check collision with walls
    if (tileCollision.CheckCollision(GetBoundingBox())) 
    {
        // Revert position
        enemyPosition = oldPosition;
        boxCollision.x = enemyPosition.x;
        boxCollision.y = enemyPosition.y;

        // Try both perpendicular directions and pick the first valid one
        Vector2 perpendicular1, perpendicular2;
        if (fabs(directionToPlayer.x) > fabs(directionToPlayer.y)) 
        {
            // If moving mostly horizontally, try both vertical directions
            perpendicular1 = { 0, movementSpeed * deltaTime };
            perpendicular2 = { 0, -movementSpeed * deltaTime };
        } 
        else 
        {
            // If moving mostly vertically, try both horizontal directions
            perpendicular1 = { movementSpeed * deltaTime, 0 };
            perpendicular2 = { -movementSpeed * deltaTime, 0 };
        }

        // Try the first perpendicular movement
        enemyPosition.x += perpendicular1.x;
        enemyPosition.y += perpendicular1.y;
        boxCollision.x = enemyPosition.x;
        boxCollision.y = enemyPosition.y;

        if (tileCollision.CheckCollision(GetBoundingBox())) 
        {
            // If the first attempt failed, revert and try the other direction
            enemyPosition = oldPosition;
            enemyPosition.x += perpendicular2.x;
            enemyPosition.y += perpendicular2.y;
            boxCollision.x = enemyPosition.x;
            boxCollision.y = enemyPosition.y;
        }

        // If both attempts fail, revert to the original position (fully stuck)
        if (tileCollision.CheckCollision(GetBoundingBox())) 
        {
            enemyPosition = oldPosition;
            boxCollision.x = enemyPosition.x;
            boxCollision.y = enemyPosition.y;
        }
    }

    // Update animation state
    isMoving = (enemyPosition.x != oldPosition.x || enemyPosition.y != oldPosition.y);
    
    if (isMoving) 
    {
        if (currentTexture.id != enemyWalk.id) 
        {
            currentTexture = enemyWalk;
            numFrames = 6;
            frameWidth = enemyWalk.width / numFrames;
        }
    } 
    else 
    {
        if (currentTexture.id != enemyIdle.id) 
        {
            currentTexture = enemyIdle;
            numFrames = 4;
            frameWidth = enemyIdle.width / numFrames;
        }
    }

    UpdateFrame();
}



void Enemy::UpdateFrame()
{
    framesCounter++;

    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        ++currentFrame;
        currentFrame %= numFrames;
        frameRec.x = (float)frameWidth * currentFrame;
    }
}

bool Enemy::CheckCollisionWithOtherEnemy(const Enemy& other) const
{
    return CheckCollisionRecs(boxCollision, other.boxCollision);
}

void Enemy::Attack(float deltaTime)
{
    timeSinceLastAttack += deltaTime;

    float distance = Vector2Distance(player.playerPosition, enemyPosition);
    if (distance < player.radius && timeSinceLastAttack > 1.0f) {
        player.healthPoints -= 10;
        timeSinceLastAttack = 0.0f;
        hitPlayer = true;
    } else {
        hitPlayer = false;
    }
}

bool Enemy::Destroy()
{
    if (health <= 0) {
        player.experiencePoints += 10;
        player.enemiesKilled++;
        return true;
    }
    return false;
}

void Enemy::Draw() const
{
    if (direction == RIGHT) {
        DrawTexturePro(currentTexture, frameRec, { enemyPosition.x, enemyPosition.y, frameRec.width * scale, frameRec.height * scale }, { 0, 0 }, 0.0f, WHITE);
    } else {
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTexturePro(currentTexture, flippedFrameRec, { enemyPosition.x, enemyPosition.y, frameRec.width * scale, frameRec.height * scale }, { 0, 0 }, 0.0f, WHITE);
    }

    // Draw health bar
    float healthPercentage = (float)health / maxHealth;
    float barWidth = 50.0f; // Width of the health bar
    float barHeight = 5.0f; // Height of the health bar
    Vector2 barPosition = { enemyPosition.x, enemyPosition.y - 10.0f }; // Position of the health bar above the enemy

    // Draw the background of the health bar (max health)
    DrawRectangle(barPosition.x, barPosition.y, barWidth * scale, barHeight, RED);

    // Draw the current health bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth * healthPercentage * scale, barHeight, GREEN);

    DrawRectangleLines(enemyPosition.x, enemyPosition.y, frameRec.width * scale, frameRec.height * scale, RED);
}

Rectangle Enemy::GetBoundingBox() const
{
    float newWidth = frameRec.width * scale * 2.0f / 3.0f;
    float newHeight = frameRec.height * scale * 2.0f / 3.0f;

    // Calculate the new position to center the rectangle
    float newX = enemyPosition.x + (frameRec.width * scale - newWidth) / 2.0f;
    float newY = enemyPosition.y + (frameRec.height * scale - newHeight) / 2.0f;

    return { newX, newY, newWidth, newHeight };
}