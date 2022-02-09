#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include"Select.h"
//�Z���N�g�V�[���̃I�u�W�F�N�g�}�l�[�W���[���Z���N�g�V�[���̉��o�Ǘ�
class SelectManager
{
private:
	int size;			//�X�e�[�W��
	int radius;			//�I�u�W�F�N�g�z�u�̔��a
	float division;		//�I�u�W�F�N�g�z�u�̊Ԋu
	float angle;		//���Z���ꂽ�p�x
	int lerpCount;		//��]�̃J�E���g
	int b;				//���Z������
	int j;				//�s�b�N�A�b�v���ꂽ�I�u�W�F�N�g�̗v�f�ԍ�
	int Enter;			//����L�[
	bool next;			//�X�e�[�W���������鉉�o�t���O
	int nextCount;		//���o�̃J�E���g
	float rgbshift;		//�|�X�g�G�t�F�N�g�p�ϐ�
	std::vector<Select*> object;

public:
	SelectManager();
	~SelectManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update();
	void BoxRotation();				//�X�e�[�W�I���̉�]
	void SelectContorol();			//�I����ʂ̑���Ɖ��Đ�
	void Draw(DirectXCommon* dxCommon);

	//Geter
	int GetMapSelect();
	inline int GetEnter() { return Enter; }
	inline float GetRGBShift() { return rgbshift; }
	inline std::vector<Select*>GetSelect() { return object; }
	//Seter
	void SetNext(bool b);
	void ResetClear();
};

