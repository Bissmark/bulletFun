# 🎮 BulletFun

<div align="center">

*A fast-paced bullet hell roguelike with cooldown-based abilities*

[Features](#-features) • [Installation](#-installation) • [Controls](#-controls) • [Roadmap](#-roadmap)

</div>

---

## 📖 About

BulletFun is a bullet hell roguelike game inspired by **Vampire Survivors** and **Halls of Torment**, with a unique twist on the genre. Instead of passive auto-attacking abilities, BulletFun introduces **cooldown-based active abilities** that require strategic timing and positioning to defeat waves of enemies.

### 🎯 What Makes BulletFun Different?

- **Active Ability System**: Collect and manage cooldown-based abilities rather than passive auto-attacks
- **Strategic Combat**: Timing and positioning matter - activate abilities at the right moment to maximize effectiveness
- **Roguelike Progression**: Permanent unlocks combined with run-specific upgrades
- **Fast-Paced Action**: Dodge, position, and unleash devastating abilities against hordes of enemies

---

## 🛠️ Built With

| Technology | Purpose |
|------------|---------|
| **C++** | Core game logic and systems |
| **Raylib** | Graphics rendering and game framework |
| **ImGui** | Debug UI and developer tools |
| **Tiled** | Level design and tilemap creation |
| **CMake** | Cross-platform build system |

---

## 🚀 Installation

git clone https://github.com/Bissmark/bulletFun.git
cd bulletFun

mkdir build
cd build

cmake ..

cmake --build . --config Release
```

---

## 🎮 Controls

| Action | Key |
|--------|-----|
| Move Up | `W` |
| Move Down | `S` |
| Move Left | `A` |
| Move Right | `D` |
| Ability 1 | `Q` |
| Ability 2 | `E` |
| Ability 3 | `R` |
| Ability 4 | `F` |
| Pause Menu | `ESC` |

---

## 🗺️ Roadmap

### Phase 1: Core Systems ✅
- [x] Movement and controls
- [x] Basic rendering pipeline
- [x] Enemy spawning system
- [x] Collision detection
- [x] Audio system

### Phase 2: Gameplay (In Progress) 🚧
- [ ] Cooldown ability system
- [ ] Multiple ability types (projectile, area, buff)
- [ ] Fix the shader issues
- [ ] Enemy variety and behaviors
- [ ] Power-up and upgrade system
- [ ] Win/lose conditions

### Phase 3: Content & Polish
- [ ] Multiple playable characters
- [ ] 10+ unique abilities
- [ ] Boss encounters
- [ ] Meta progression system
- [ ] Particle effects and visual polish
- [ ] Sound effects and music

---

## 🎯 Design Philosophy

BulletFun is designed around three core principles:

1. **Active Engagement** - Players should constantly make meaningful decisions, not watch auto-attacks
2. **Strategic Depth** - Ability combinations and timing create emergent gameplay
3. **Satisfying Progression** - Both short-term (run-based) and long-term (meta) rewards

---

## 🙏 Acknowledgments

- **Vampire Survivors** by Poncle - Inspiration for the survivor genre
- **Halls of Torment** by Chasing Carrots - Inspiration for visual style and pacing
- **Raylib** community - Excellent game development framework
- **Tiled** by Thorbjørn Lindeijer - Fantastic map editor
- All playtesters and contributors!

---