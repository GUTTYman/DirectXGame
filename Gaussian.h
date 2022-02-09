#pragma once
#include "Sprite.h"


class Gaussian :
    public Sprite
{
private:
    struct GaussianData {
        float shiftweight = 0.000f;
        float rgbShiftWeight = 0.000f;
        float time = 0.0f;
    };

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Gaussian();
    /// <summary>
    /// ������
    /// </summary>
    void Initialize();
    /// <summary>
    /// �`��O����
    /// </summary>
    /// <param name="cmdList"></param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
    /// <summary>
    /// �`��㏈��
    /// </summary>
    /// <param name="cmdList"></param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    void CreateGraphicsPiepelineState();
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="cmdList"></param>
    void Draw(ID3D12GraphicsCommandList* cmdList);
    //Setter
    void SetShift(float sw) { shiftweight = sw; }
    void SetRGBShift(float sw) { rgbShiftWeight = sw; }
    //Getter
    Gaussian* GetGaussianData();
private:
    ComPtr<ID3D12Resource>texBuff[2];
    ComPtr<ID3D12Resource>depthBuff;
    ComPtr<ID3D12Resource> cb;

    ComPtr<ID3D12DescriptorHeap>descHeapSRV;
    ComPtr<ID3D12DescriptorHeap>descHeapRTV;
    ComPtr<ID3D12DescriptorHeap>descHeapDSV;
    
    ComPtr<ID3D12PipelineState>piepelineState;
    ComPtr<ID3D12RootSignature>rootSignature;
    
    //��ʃN���A�J���[
    static const float clearColor[4];  
    //�ȉ��萔�o�b�t�@�p�ϐ�
    float shiftweight = 0.0f;
    float rgbShiftWeight = 0.000f;
    float time = 0.0f;
};