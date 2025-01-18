#include "skillBar.h"

SkillBar::SkillBar()
{
}

void SkillBar::Update()
{
}

void SkillBar::Draw() const
{
    int mainBoxWidth = 300;
    int mainBoxHeight = 200;
    int mainBoxX = GetScreenWidth() / 2 - mainBoxWidth / 2;
    int mainBoxY = GetScreenHeight() / 2 - mainBoxHeight / 2;
    DrawRectangle(mainBoxX, mainBoxY, mainBoxWidth + 20, mainBoxHeight, BLUE);
}