#pragma once
#include "GameBase.h"
#include "PostEffect.h"
#include "Gaussian.h"

#include"TitleScene.h"
#include"SelectScene.h"
#include"GamePlayScene.h"
#include"ResultScene.h"


#include<memory>


class DirectXGame :
    public GameBase
{
public:
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
protected:
   
private:

    //ポストエフェクト
    std::unique_ptr < PostEffect> postEffect;
    std::unique_ptr < Gaussian> gaussian;

    D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleCBV;
    D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

    std::unique_ptr < TitleScene> titleScene;
    std::unique_ptr < SelectScene> selectScene;
    std::unique_ptr < GamePlayScene> gameplayScene;
    std::unique_ptr < ResultScene> resultScene;
};

