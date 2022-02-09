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
    void OpeningUpdate();   //�J�n�����o�̍X�V
    void ChangeMap();       //�}�b�v�؂�ւ�
private:
    //�ŏ��̉��o
    Opening* opening;
};
