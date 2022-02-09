#pragma once
#include "Scene.h"
class TitleScene
    :Scene
{
private:
    bool start = false;
    int titleCount = 120;
public:
    ~TitleScene();
    void Update()override;
    void Draw()override;

};

