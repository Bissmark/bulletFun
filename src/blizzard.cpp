#include "blizzard.h"

Blizzard::Blizzard(float radius, int speed, int baseDamage, Color color)
    : radius(radius)
    , speed(speed)
    , baseDamage(baseDamage)
    , color(color)
    , cooldown(0.0f)
    , cooldownTime(5.0f)
    , elapsedTime(0.0f)
    , isActive(false)
    , name("Blizzard")
{
}

void Blizzard::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    elapsedTime += deltaTime;

    if (elapsedTime >= cooldownTime) {
        isActive = false;
        elapsedTime = 0.0f;
    }

    if (isActive) {
        for (auto& enemy : enemies) {
            if (CheckCollision(player, *enemy)) {
                enemy->health -= baseDamage;
                if (enemy->health <= 0) {
                    enemy->Destroy();
                }
            }
        }
    }
}

void Blizzard::Activate()
{
    if (elapsedTime >= cooldownTime) {
        isActive = true;
    }
}

void Blizzard::Draw(const Player& player, const Camera2D& camera) const
{
    if (isActive) {
        DrawCircleV(centerPosition, radius, color);
    }
}

bool Blizzard::CheckCollision(const Player& player, Enemy& enemy)
{
    return CheckCollisionCircleRec(centerPosition, radius, enemy.GetBoundingBox());
}

float Blizzard::GetCooldownTime() const
{
    return cooldownTime;
}

float Blizzard::GetCooldownDuration() const
{
    return cooldown;
}

std::string Blizzard::GetName() const
{
    return name;
}

int Blizzard::GetDamage() const
{
    return baseDamage;
}
