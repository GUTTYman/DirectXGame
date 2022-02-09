#include "SelectManager.h"
SelectManager::SelectManager()
{
	size = 6;
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Select());
	}
}

SelectManager::~SelectManager()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void SelectManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	radius = 30;
	division = (628.0f / size) / 100;
	angle = 0.0f;
	b = 0;
	j = 0;
	Enter = 0;
	lerpCount = 0;
	nextCount = 0;
	next = false;
	rgbshift = 0.0f;
	//�e�I�u�W�F�N�g�̏�����
	object[0]->Initialize(dxCommon, textureManager, SELECTBOX1);
	object[1]->Initialize(dxCommon, textureManager, SELECTBOX2);
	object[2]->Initialize(dxCommon, textureManager, SELECTBOX3);
	object[3]->Initialize(dxCommon, textureManager, SELECTBOX4);
	object[4]->Initialize(dxCommon, textureManager, SELECTBOX5);
	object[5]->Initialize(dxCommon, textureManager, SELECTBOX6);

	for (int i = 0; i < object.size(); i++)
	{
		object[i]->SetPosition(Vector3(sinf(division * i) * radius,
			object[i]->GetPosition().y,
			cosf(division * i) * radius));
		object[i]->Update();

	}
	object[0]->SetOpen(true);
	object[0]->SetTexture(11);
}

void SelectManager::Update()
{
#pragma region �X�e�[�W�I����ʂ̑���
	//���o������Ȃ��ꍇ
	if (!next)
	{
		//�A�łł��Ȃ��悤��]���͐������X�e�[�W������
		if (abs(division * b - angle) == 0.0f && Enter == 0)
		{
			//�I����ʂ̑���Ɖ��Đ�
			SelectContorol();
		}
	}
	//�X�e�[�W�����肵����
	if (Enter == 1)
	{
		//�X�e�[�W���������Ă��邩�ǂ���
		if (object[j % size]->GetOpen())
		{
			//�X�e�[�W���肵����傫�������Z�����
			object[j % size]->SetScale(object[j % size]->GetScale() += Vector3(1,1,1));
			if (object[j % size]->GetScale().x > 40)
			{
				Enter = 2;
			}
		}
		else
		{
			//�U��������
			object[j % size]->SetShakeVelosity(Vector2(30.0f, 0.0f));
			Enter = 0;
		}
	}

	//�}�C�i�X�s������Ō���ɖ߂�
	if (j < 0)
	{
		j = object.size() - 1;
	}
#pragma endregion

	BoxRotation();

#pragma region �X�e�[�W�J�����o
	if (next)
	{
		static float end = 60;
		static float effectcount = 120;
		nextCount++;

		if (nextCount == 60)
		{
			//�����Ŏ��̃}�b�v�ɉ�]
			b--;
			j++;

		}
		else if (nextCount == effectcount)
		{
			//���̃X�e�[�W�����
			for (int i = 0; i < size; i++)
			{
				if (!object[i]->GetOpen())
				{
					object[i]->SetOpen(true);
					object[i]->SetTexture(11 + i);
					object[i]->SetCount(0.0f);
					//�������Đ�
					GameObject::GetSoundManager()->PlayWave(AudioIndex::EXPLOSION2);
					break;
				}
			}

		}
		else if (nextCount > effectcount && nextCount < effectcount + end)//
		{
			rgbshift = easeOut(Vector3(0.05f, 0.0f, 0.0f), Vector3(), (nextCount - effectcount) / end).x;
		}
		else if (nextCount > effectcount + end)//�I��
		{
			//�l��������
			next = false;
			nextCount = 0;
		}

	}
#pragma endregion

}

void SelectManager::BoxRotation()
{
	static float currentAngle;	//���[�v���̍ŏ��p�x
	if (angle != division * b)
	{
		lerpCount++;
		//�p�x����]
		angle = lerp(currentAngle, division * b, lerpCount / 20.0f);
	}
	else
	{
		//���݂̊p�x��n��
		currentAngle = angle;
		lerpCount = 0;
	}
		

	for (int i = 0; i < object.size(); i++)
	{
		if (Enter == 0)
		{
			//��]�ƃ|�W�V�����w��@+�@�������ĂȂ��̂ɑI���������̐U���l
			object[i]->SetPosition(Vector3(sinf(division * i + angle - (division * 3)) * radius, object[i]->GetPosition().y, cosf(division * i + angle - (division * 3)) * radius) + object[i]->GetShake());
			if (i == j % size)
			{
				//��Ԏ�O�̃I�u�W�F�N�g���s�b�N�A�b�v
				object[i]->SetScale(Vector3(8, 8, 3));;
				object[i]->SetMoving(true);
				object[i]->SetisRota(true);
			}
			else
			{
				//����ȊO�͒ʏ�T�C�Y
				object[i]->SetScale(Vector3(2, 2, 2));
				object[i]->SetMoving(false);
			}
		}
		object[i]->Update();
	}
}

void SelectManager::SelectContorol()
{
	//�L�[�{�[�h����
	if (GameObject::GetInput()->Trigger(DIK_RIGHT) || GameObject::GetInput()->Trigger(DIK_LEFT))
	{
		if (GameObject::GetInput()->Trigger(DIK_RIGHT))
		{
			b++;
			j--;
		}
		if (GameObject::GetInput()->Trigger(DIK_LEFT))
		{
			b--;
			j++;
		}
		GameObject::GetSoundManager()->PlayWave(AudioIndex::SELECT);
	}
	else
	{

		//�p�b�hL�X�e�B�b�N����
		if (GameObject::GetPad()->LStickXTrigger())
		{
			GameObject::GetSoundManager()->PlayWave(AudioIndex::SELECT);
			if (GameObject::GetPad()->GetLStickX() > 0.0f)
			{
				b++;
				j--;
			}
			else if (GameObject::GetPad()->GetLStickX() < 0.0f)
			{
				b--;
				j++;
			}
		}
	}
	//�X�e�[�W����
	if (GameObject::GetInput()->Trigger(DIK_SPACE) || GameObject::GetPad()->Trigger(XINPUT_A))
	{
		Enter = 1;
		//�X�e�[�W���������Ă��邩�ǂ���
		if (object[j % size]->GetOpen())
		{
			//���艹
			GameObject::GetSoundManager()->PlayWave(AudioIndex::PICKUP);
		}
		else
		{
			//�L�����Z�����Đ�
			GameObject::GetSoundManager()->PlayWave(AudioIndex::DONOT);
		}
	}

}

void SelectManager::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}
int SelectManager::GetMapSelect()
{
	Enter = 0;
	return j % size;
}

void SelectManager::SetNext(bool b)
{
	if (!object[(j + 1) % size]->GetOpen())
	{
		next = b;
	}
}
//�X�e�[�W����������������
void SelectManager::ResetClear()
{
	//�X�e�[�W�P��擪�Ɏ����Ă���
	b = 0;
	j = 0;
	for (int i = 1; i < size; i++)
	{
		object[i]->SetOpen(false);
		object[i]->SetTexture(10);
		object[i]->SetRotation(Vector3());
		object[i]->SetPosition(Vector3(object[i]->GetPosition().x, object[0]->GetPosition().y, object[i]->GetPosition().z));
	}
}

