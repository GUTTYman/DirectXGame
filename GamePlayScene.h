#pragma once
#include "Scene.h"
#include "Opening.h"
class GamePlayScene
    :Scene
{

public:
    ~GamePlayScene();
    void Initialize();
    void Update()override;
    void Draw()override;
    void OpeningUpdate();   //開始時演出の更新
    void ChangeMap();       //マップ切り替え
private:
    //最初の演出
    Opening* opening;
};

