#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "slash.h"
#include <iostream>
#include <raymath.h>
#include <limits>

Player::Player()
    : healthPoints(100)
    , speedX(5)
    , speedY(5)
    , radius(15)
    , boxCollision({ 0 })
    , currentEnemiesKilled(0)
    , startTime(GetTime())
    , elapsedTime(0.0)
    , gamePaused(false)
    , auraDmg(50.0f, 10, RED)
{
    currentFrame = 0;

    framesCounter = 0;
    framesSpeed = 5;

    level = 1;
    experiencePoints = 0;
    maxExperiencePoints = 100;
    attackSpeed = 1;

    baseDamage = 10;
    critChance = 5.0f;
    critDamage = 2;

    playerIdle = LoadTexture("src/Spritesheet/player/Idle.png");
    playerWalk = LoadTexture("src/Spritesheet/player/Walk.png");

    numFrames = 4;
    frameWidth = playerIdle.width / numFrames;

    currentTexture = playerIdle;

    leveledUp = false;

    frameRec = { 0.0f, 0.0f, (float)playerIdle.width / numFrames, (float)playerIdle.height };
    playerPosition = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
}

void Player::Update()
{
    frameRec.x = (float)currentFrame * (float)currentTexture.width / numFrames;

    for (auto& bullet : bullets) {
        bullet.Move();
    }

    LevelUp();

    elapsedTime = GetTime() - startTime;

    auraDmg.Update(*this);
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

    for (auto& enemy : enemies) {
        auraDmg.Collision(playerPosition, *enemy);
    }
}

void Player::LevelUp()
{
    if (experiencePoints >= maxExperiencePoints) {
        experiencePoints = 0;
        maxExperiencePoints *= 2;
        leveledUp = true;
        gamePaused = true;
        level++;
    }
}

void Player::DrawLevelUpBox()
{
    if (leveledUp) {
        // Draw the main blue box
        int mainBoxWidth = 300;
        int mainBoxHeight = 200;
        int mainBoxX = GetScreenWidth() / 2 - mainBoxWidth / 2;
        int mainBoxY = GetScreenHeight() / 2 - mainBoxHeight / 2;
        DrawRectangle(mainBoxX, mainBoxY, mainBoxWidth + 20, mainBoxHeight, BLUE);

        // Draw three smaller boxes inside the main box
        int smallBoxWidth = 80;
        int smallBoxHeight = 80;
        int spacing = 20;
        int smallBoxY = mainBoxY + (mainBoxHeight - smallBoxHeight) / 2;

        for (int i = 0; i < 3; ++i) {
            int smallBoxX = mainBoxX + spacing + i * (smallBoxWidth + spacing);
            DrawRectangle(smallBoxX, smallBoxY, smallBoxWidth, smallBoxHeight, WHITE);

            // Draw textures inside the smaller boxes (replace with actual textures)
            // Example: DrawTexture(texture, smallBoxX, smallBoxY, WHITE);
            // For now, we'll just draw a placeholder rectangle
            DrawRectangle(smallBoxX + 10, smallBoxY + 10, smallBoxWidth - 20, smallBoxHeight - 20, GRAY);
        
            // Check for mouse clicks within the bounding rectangles of the small boxes
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, { (float)smallBoxX, (float)smallBoxY, (float)smallBoxWidth, (float)smallBoxHeight })) {
                    leveledUp = false;
                    gamePaused = false;
                }
            }
        }
    }
}

void Player::Draw() const
{
    if (direction == RIGHT) {
        DrawTextureRec(currentTexture, frameRec, playerPosition, WHITE);
    } else {
        // Flip the texture horizontally
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTextureRec(currentTexture, flippedFrameRec, playerPosition, WHITE);
    }

    for (auto& bullet : bullets) {
        bullet.Draw();
    }

    auraDmg.Draw(*this);
}

void Player::DrawExp() const
{
    float expPercentage = (float)experiencePoints / maxExperiencePoints;
    float barWidth = 650.0f;
    float barHeight = 15.0f;
    Vector2 barPosition = { GetScreenWidth() / 10.0f, GetScreenHeight() - 40.0f };

    // Draw background of the exp bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth, barHeight, GRAY);

    // Draw the exp bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth * expPercentage, barHeight, GOLD);
}