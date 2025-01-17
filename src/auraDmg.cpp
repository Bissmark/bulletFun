#include "auraDmg.h"
// #include "player.h"
// #include "enemy.h"
#include <raymath.h>

AuraDmg::AuraDmg(float radius, int baseDamage, Color color)
    : radius(radius), baseDamage(baseDamage), color(color)
{

}

void AuraDmg::Update(const Player& player)
{

}

bool AuraDmg::CheckCollision(const Player& player, Enemy& enemy)
{
    float distance = Vector2Distance(enemy.enemyPosition, player.playerPosition);
    if (distance <= radius) {
        enemy.health -= baseDamage;
        if (enemy.health <= 0) {
            enemy.Destroy();
        }
        return true;
    }
    return false;
}

void AuraDmg::Draw(const Player& player) const
{
    Vector2 centerPosition = { player.playerPosition.x + player.frameRec.width / 2, player.playerPosition.y + player.frameRec.height / 2 };
    DrawCircleV(centerPosition, radius, Fade(color, 0.5f));
}