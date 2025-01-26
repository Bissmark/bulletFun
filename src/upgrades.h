#pragma once
#include <raylib.h>

enum class UpgradeType {
    CritChance,
    CritDamage,
    CooldownReduction,
    Health,
    Damage
};

struct Upgrade {
    UpgradeType type;
    const char* name;
    const char* description;
    const Texture2D* texture;
};