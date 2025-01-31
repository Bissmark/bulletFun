#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "slash.h"
#include "ability.h"
#include <iostream>
#include <raymath.h>
#include <limits>

Player::Player()
    : speedX(2)
    , speedY(2)
    , radius(15)
    , currentEnemiesKilled(0)
    , startTime(GetTime())
    , elapsedTime(0.0)
    , gamePaused(false)
    , scale(0.5f)
    , enemiesKilled(0)
{
    currentFrame = 0;

    framesCounter = 0;
    framesSpeed = 5;

    level = 1;
    experiencePoints = 0;
    maxExperiencePoints = 100;
    attackSpeed = 1;

    healthPoints = 100;
    maxHealth = 100;

    baseDamage = 10;
    critChance = 5;
    critDamage = 2;

    playerIdle = LoadTexture("Spritesheet/player/Idle.png");
    playerWalk = LoadTexture("Spritesheet/player/Walk.png");

    numFrames = 4;
    frameWidth = playerIdle.width / numFrames;

    currentTexture = playerIdle;

    leveledUp = false;
    leveledUpWindowActive = false;

    frameRec = { 0.0f, 0.0f, (float)playerIdle.width / numFrames, (float)playerIdle.height };
    playerPosition = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
}

void Player::Update(std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    frameRec.x = (float)currentFrame * (float)currentTexture.width / numFrames;

    for (auto& bullet : bullets) {
        bullet.Move();
    }

    PlayerLevelUp();

    //elapsedTime = GetTime() - startTime;

    abilityManager.Update(*this, enemies, deltaTime);
}

void Player::Move()
{
    bool isMoving = false;

    if (IsKeyDown(KEY_D)) {
        playerPosition.x += speedX;
        isMoving = true;
        direction = RIGHT;
    }
    if (IsKeyDown(KEY_A)) {
        playerPosition.x -= speedX;
        isMoving = true;
        direction = LEFT;
    }
    if (IsKeyDown(KEY_W)) {
        playerPosition.y -= speedY;
        isMoving = true;
    }
    if (IsKeyDown(KEY_S)) {
        playerPosition.y += speedY;
        isMoving = true;
    }

    if (isMoving) {
        if (currentTexture.id != playerWalk.id) {
            currentTexture = playerWalk;
            numFrames = 6;
            frameWidth = playerWalk.width / numFrames;
        }
    } else {
        if (currentTexture.id != playerIdle.id) {
            currentTexture = playerIdle;
            numFrames = 4;
            frameWidth = playerIdle.width / numFrames;
        }
    }

    UpdateFrame();
}

void Player::UpdateFrame()
{
    ++framesCounter;

    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        ++currentFrame;
        currentFrame %= numFrames;
        frameRec.x = (float)frameWidth * currentFrame;
    }
}

// void Player::Fire(const Camera2D& camera)
// {
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         Vector2 mousePosition = GetMousePosition();
//         Vector2 screenPlayerPosition = GetWorldToScreen2D(playerPosition, camera);
//         Vector2 direction = Vector2Subtract(mousePosition, screenPlayerPosition);
//         direction = Vector2Normalize(direction);
//         bullets.push_back(Bullet(playerPosition, direction, attackSpeed, BLUE, this));
//     }
// }

Enemy* Player::FindClosestEnemy(std::vector<std::unique_ptr<Enemy>>& enemies)
{
    Enemy* closestEnemy = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (auto& enemy : enemies) {
        float distance = Vector2Distance(playerPosition, enemy->enemyPosition);
        if (distance < closestDistance) {
            closestDistance = distance;
            closestEnemy = enemy.get();
        }
    }

    return closestEnemy;
}

void Player::AutoAttack(std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    static float timeSinceLastAttack = 0.0f;
    timeSinceLastAttack += deltaTime;

    const float bulletSpeed = 5.0f;
    const float slashRadius = 50.0f;

    if (timeSinceLastAttack >= 1.0f / attackSpeed) {
        Enemy* closestEnemy = FindClosestEnemy(enemies);
        if (closestEnemy) {
            Vector2 direction = Vector2Subtract(closestEnemy->enemyPosition, playerPosition);
            direction = Vector2Normalize(direction);
            
            switch (playerType) {
                case PlayerType::ARCHER:
                    bullets.push_back(Bullet(playerPosition, direction, bulletSpeed, BLUE, this));
                    break;
                case PlayerType::MAGE:
                    bullets.push_back(Bullet(playerPosition, direction, bulletSpeed, BLUE, this));
                    break;
                case PlayerType::WARRIOR:
                    Slash slash(playerPosition, direction, slashRadius, this);
                    for (auto& enemy : enemies) {
                        if (slash.Collision(*enemy)) {
                            int damage = baseDamage;
                            if (GetRandomValue(1, 100) <= critChance) {
                                damage *= critDamage;
                            }
                            enemy->health -= damage;
                            if (enemy->health <= 0) {
                                enemy->Destroy();
                            }
                        }
                    }
                    break;
            }
        }
        timeSinceLastAttack = 0.0f;
    }

    abilityManager.CheckCollisions(*this, enemies);
}

void Player::PlayerLevelUp()
{
    if (experiencePoints >= maxExperiencePoints) {
        experiencePoints = 0;
        maxExperiencePoints *= 2;
        leveledUp = true;
        leveledUpWindowActive = true;
        gamePaused = true;
        level++;
    }
}

// void Player::DrawLevelUpBox()
// {
//     levelUp.DrawLevelUpBox();
// }

void Player::Draw(const Camera2D& camera) const
{
    if (direction == RIGHT) {
        DrawTexturePro(currentTexture, frameRec, { playerPosition.x, playerPosition.y, frameRec.width * scale, frameRec.height * scale }, { 0, 0 }, 0.0f, WHITE);
    } else {
        // Flip the texture horizontally
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTexturePro(currentTexture, flippedFrameRec, { playerPosition.x, playerPosition.y, frameRec.width * scale, frameRec.height * scale }, { 0, 0 }, 0.0f, WHITE);
    }

    for (auto& bullet : bullets) {
        bullet.Draw(camera);
    }

    abilityManager.Draw(*this, camera);

    // Calculate the new width and height (2/3rds of the current size)
    float newWidth = frameRec.width * scale * 2.0f / 3.0f;

    // Calculate the new position to center the rectangle
    float newX = playerPosition.x + (frameRec.width * scale - newWidth) / 2.0f;

    // Draw the rectangle lines with the adjusted dimensions
    //DrawRectangleLines(newX, playerPosition.y, newWidth, frameRec.height * scale, RED);
}

void Player::DrawExp() const
{
    float expPercentage = (float)experiencePoints / maxExperiencePoints;
    float barWidth = 25.0f;
    float barHeight = GetScreenHeight() - 80.0f;
    Vector2 barPosition = { GetScreenWidth() - barWidth - 10.0f, GetScreenHeight() / 2 - barHeight / 2 };

    // Draw background of the exp bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth, barHeight, GRAY);

    // Draw the exp bar
    float filledHeight = barHeight * expPercentage;
    float filledY = barPosition.y + (barHeight - filledHeight);
    DrawRectangle(barPosition.x, filledY, barWidth, filledHeight, GOLD);
}

void Player::AddAbility(std::unique_ptr<Ability> ability)
{
    abilityManager.AddAbility(std::move(ability));
}

Rectangle Player::GetBoundingBox() const
{   
    float newWidth = frameRec.width * scale * 2.0f / 3.0f;
    float newHeight = frameRec.height * scale * 2.0f / 3.0f;

    // Calculate the new position to center the rectangle
    float newX = playerPosition.x + (frameRec.width * scale - newWidth) / 2.0f;
    float newY = playerPosition.y + (frameRec.height * scale - newHeight) / 2.0f;

    return { newX, newY, newWidth, newHeight };
}