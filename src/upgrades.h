#pragma once
#include <raylib.h>

enum class UpgradeType {
    CritChance,
    CritDamage,
    CooldownReduction,
    Health,
    Damage,
};

enum class Rarity {
    Common,
    Rare,
    Epic,
};

struct Upgrade {
    UpgradeType type;
    const char* name;
    const char* description;
    const Texture2D* texture;
    Rarity rarity;
    float increaseAmount;
    Color color;
};