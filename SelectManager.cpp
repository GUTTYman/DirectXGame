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
	//各オブジェクトの初期化
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
#pragma region ステージ選択画面の操作
	//演出中じゃない場合
	if (!next)
	{
		//連打できないよう回転中は制限＆ステージ未決定
		if (abs(division * b - angle) == 0.0f && Enter == 0)
		{
			//選択画面の操作と音再生
			SelectContorol();
		}
	}
	//ステージを決定したら
	if (Enter == 1)
	{
		//ステージが解放されているかどうか
		if (object[j % size]->GetOpen())
		{
			//ステージ決定したら大きさが加算される
			object[j % size]->SetScale(object[j % size]->GetScale() += Vector3(1,1,1));
			if (object[j % size]->GetScale().x > 40)
			{
				Enter = 2;
			}
		}
		else
		{
			//振動させる
			object[j % size]->SetShakeVelosity(Vector2(30.0f, 0.0f));
			Enter = 0;
		}
	}

	//マイナス行ったら最後尾に戻る
	if (j < 0)
	{
		j = object.size() - 1;
	}
#pragma endregion

	BoxRotation();

#pragma region ステージ開放演出
	if (next)
	{
		static float end = 60;
		static float effectcount = 120;
		nextCount++;

		if (nextCount == 60)
		{
			//自動で次のマップに回転
			b--;
			j++;

		}
		else if (nextCount == effectcount)
		{
			//次のステージを解放
			for (int i = 0; i < size; i++)
			{
				if (!object[i]->GetOpen())
				{
					object[i]->SetOpen(true);
					object[i]->SetTexture(11 + i);
					object[i]->SetCount(0.0f);
					//解除音再生
					GameObject::GetSoundManager()->PlayWave(AudioIndex::EXPLOSION2);
					break;
				}
			}

		}
		else if (nextCount > effectcount && nextCount < effectcount + end)//
		{
			rgbshift = easeOut(Vector3(0.05f, 0.0f, 0.0f), Vector3(), (nextCount - effectcount) / end).x;
		}
		else if (nextCount > effectcount + end)//終了
		{
			//値を初期化
			next = false;
			nextCount = 0;
		}

	}
#pragma endregion

}

void SelectManager::BoxRotation()
{
	static float currentAngle;	//ラープ時の最初角度
	if (angle != division * b)
	{
		lerpCount++;
		//角度を回転
		angle = lerp(currentAngle, division * b, lerpCount / 20.0f);
	}
	else
	{
		//現在の角度を渡す
		currentAngle = angle;
		lerpCount = 0;
	}
		

	for (int i = 0; i < object.size(); i++)
	{
		if (Enter == 0)
		{
			//回転とポジション指定　+　解放されてないのに選択した時の振動値
			object[i]->SetPosition(Vector3(sinf(division * i + angle - (division * 3)) * radius, object[i]->GetPosition().y, cosf(division * i + angle - (division * 3)) * radius) + object[i]->GetShake());
			if (i == j % size)
			{
				//一番手前のオブジェクトをピックアップ
				object[i]->SetScale(Vector3(8, 8, 3));;
				object[i]->SetMoving(true);
				object[i]->SetisRota(true);
			}
			else
			{
				//それ以外は通常サイズ
				object[i]->SetScale(Vector3(2, 2, 2));
				object[i]->SetMoving(false);
			}
		}
		object[i]->Update();
	}
}

void SelectManager::SelectContorol()
{
	//キーボード操作
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

		//パッドLスティック操作
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
	//ステージ決定
	if (GameObject::GetInput()->Trigger(DIK_SPACE) || GameObject::GetPad()->Trigger(XINPUT_A))
	{
		Enter = 1;
		//ステージが解放されているかどうか
		if (object[j % size]->GetOpen())
		{
			//決定音
			GameObject::GetSoundManager()->PlayWave(AudioIndex::PICKUP);
		}
		else
		{
			//キャンセル音再生
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
//ステージ解除を初期化する
void SelectManager::ResetClear()
{
	//ステージ１を先頭に持ってくる
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

