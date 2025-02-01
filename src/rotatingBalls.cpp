#include "rotatingBalls.h"
#include <cmath>
#include <raymath.h>
#include <iostream>

RotatingBalls::RotatingBalls(float cooldown, int baseDamage, float radius, float speed, int numBalls, Color color)
    : cooldown(cooldown), cooldownTime(0.0f), radius(radius), speed(speed),
      numBalls(numBalls), isShooting(false), color(color), name("Rotating Balls"), baseDamage(baseDamage)
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
    } else {
        for (auto& ball : balls)
        {
            ball.position = Vector2Add(ball.position, ball.velocity);
        }

        // If cooldown is done, reset back to orbit mode
        if (cooldownTime <= 0.0f)
        {
            isShooting = false;
            for (auto& ball : balls)
            {
                ball.velocity = { 0.0f, 0.0f }; // Reset velocity
                ball.hitEnemies.clear(); // Clear hit enemies
            }
        }
    }

    for (auto& enemy : enemies)
    {
        CheckCollision(player, *enemy);
    }
}

void RotatingBalls::Activate()
{
    if (cooldownTime <= 0.0f)
    {
        isShooting = true;
        cooldownTime = cooldown;
        for (auto& ball : balls)
        {
            int ballSpeed = 5;
            ball.velocity = { cos(ball.angle) * ballSpeed, sin(ball.angle) * ballSpeed };
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
    for (auto& ball : balls)
    {
        if (ball.hitEnemies.find(&enemy) == ball.hitEnemies.end() && // If enemy not already hit
            CheckCollisionCircles(ball.position, radius, enemy.enemyPosition, enemy.radius))
        {
            int damage = isShooting ? baseDamage : baseDamage / 2;
            enemy.health -= damage;

            ball.hitEnemies.insert(&enemy); // Mark enemy as hit by this ball

            if (enemy.health <= 0)
            {
                enemy.Destroy();
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

int RotatingBalls::GetDamage() const
{
    return baseDamage;
}