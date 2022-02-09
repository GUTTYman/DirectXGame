#pragma once
#include "Scene.h"
class SelectScene
    :Scene
{

public:
    ~SelectScene();
    void Update()override;
    void Draw()override;
    static SelectManager* GetSelectManagerObject() { return select; }
private:

};

