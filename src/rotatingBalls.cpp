#include "rotatingBalls.h"
#include <cmath>
#include <raymath.h>
#include <iostream>

RotatingBalls::RotatingBalls(float cooldown, int baseDamage, float radius, float speed, int numBalls, Color color)
    : cooldown(cooldown), cooldownTime(0.0f), radius(radius), speed(speed),
      numBalls(numBalls), isShooting(false), color(color), name("Rotating Balls"), baseDamage(baseDamage), elapsedTime(0.0f)
{
    balls.resize(numBalls);
    for (int i = 0; i < numBalls; ++i)
    {
        balls[i].angle = (2 * PI / numBalls) * i;  // Evenly distribute angles
    }
}

void RotatingBalls::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (cooldownTime > 0.0f) {
        cooldownTime -= deltaTime;
    }

    Vector2 adjustedCenterPosition = {
        player.playerPosition.x + (player.frameRec.width * player.scale) / 2.0f,
        player.playerPosition.y + (player.frameRec.height * player.scale) / 2.0f
    };

    if (!isShooting) // Orbiting phase
    {
        for (int i = 0; i < numBalls; ++i)
        {
            float angle = balls[i].angle + deltaTime * speed;
            balls[i].position = {
                adjustedCenterPosition.x + radius * cos(angle),
                adjustedCenterPosition.y + radius * sin(angle)
            };
            balls[i].angle = angle; // Store updated angle
        }


        // Fire the balls outward
        if (IsKeyPressed(KEY_SPACE)) // Change to actual input method
        {
            isShooting = true;
            elapsedTime = 0.0f;
            cooldownTime = cooldown;
            for (auto& ball : balls)
            {
                int ballSpeed = 5;
                ball.velocity = { cos(ball.angle) * ballSpeed, sin(ball.angle) * ballSpeed };
            }
        }
    }
    else // Shooting phase
    {
        elapsedTime += deltaTime;

        for (auto& ball : balls)
        {
            ball.position = Vector2Add(ball.position, ball.velocity);
        }

        // If cooldown is done, reset back to orbit mode
        if (cooldownTime <= 0.0f)
        {
            isShooting = false;
            for (int i = 0; i < numBalls; ++i)
            {
                balls[i].velocity = { 0.0f, 0.0f }; // Reset velocity
            }
        }
    }
}

void RotatingBalls::Activate()
{
    if (cooldownTime <= 0.0f)
    {
        isShooting = false; // Reset shooting state
        cooldownTime = cooldown;

        for (int i = 0; i < numBalls; ++i)
        {
            balls[i].velocity = { 0.0f, 0.0f }; // Reset velocity
        }
    }
}

void RotatingBalls::Draw(const Player& player, const Camera2D& camera) const
{
    for (const auto& ball : balls)
    {
        Vector2 screenPosition = GetWorldToScreen2D(ball.position, camera);
        DrawCircleV(screenPosition, 10.0f, color);
    }
}

bool RotatingBalls::CheckCollision(const Player& player, Enemy& enemy)
{
    for (const auto& ball : balls)
    {
        if (CheckCollisionCircles(ball.position, radius, enemy.enemyPosition, enemy.radius))
        {
            enemy.health -= baseDamage; // Change this to whatever your base damage should be
            std::cout << "Enemy Hit!" << std::endl;
            if (enemy.health <= 0)
            {
                enemy.Destroy(); // Ensure Enemy class has a Destroy() method
            }
            return true;
        }
    }
    return false;
}

float RotatingBalls::GetCooldownTime() const
{
    return cooldownTime;
}

float RotatingBalls::GetCooldownDuration() const
{
    return cooldown;
}

std::string RotatingBalls::GetName() const
{
    return name;
}
