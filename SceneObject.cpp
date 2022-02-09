#include "SceneObject.h"

SceneObject::SceneObject()
{
	titleObject = std::make_unique< Object3d>();
	clearObject = std::make_unique< Object3d>();
	goObject = std::make_unique< Object3d>();
	ButtonObject = std::make_unique< Object3d>();
	UIObject = std::make_unique< Object3d>();
	buttonBorad = std::make_unique< Object3d>();
	linkObject = std::make_unique< LinkObjectManager>(15);
}
SceneObject::~SceneObject()
{
}

//初期化
void SceneObject::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

	//TITLEのモデルをセット
	titleObject->Initialize(modelLoader->GetModel(TITLE));
	titleObject->SetOBJType(NORMALCOLOR);
	//CLEARのモデルをセット
	clearObject->Initialize(modelLoader->GetModel(CLEAR));
	clearObject->SetColor(Vector3(0,1,0));
	//GAMEOVERのモデルをセット
	goObject->Initialize(modelLoader->GetModel(GAMEOVER));
	goObject->SetColor(Vector3(1,0,0));
	//決定キーのモデルをセット
	ButtonObject->Initialize(modelLoader->GetModel(BUTTON));
	ButtonObject->SetScale(Vector3(3, 3, 3));
	ButtonObject->SetRotation(Vector3(60,180,0));
	ButtonObject->SetColor(Vector3(0.5f,0.5f,0.5f));
	//Lスティックのモデルをセット
	UIObject->Initialize(modelLoader->GetModel(LSTICK));
	UIObject->SetScale(Vector3(3,3,3));
	UIObject->SetColor(Vector3(0.5f,0.5f,0.5f));
	UIObject->SetRotation(Vector3(0,180,0));
	//ボタンボードのモデルをセット
	buttonBorad->Initialize(modelLoader->GetModel(BORAD_ABUTTON));
	boradScale = Vector3(10, 10, 20);
	boradRotation = Vector3();
	buttonBorad->SetScale(boradScale);
	linkObject->Initialize(dxCommon, textureManager);

	//シーンオブジェクト（TITLE、GAMEOVER、CLEAR）の変数
	position = Vector3(0,0,0);
	rotation = Vector3(0,180,0);
	scale = Vector3(1.0f,1.0f,1.0f);
	titleCount = 60;
	hobCount = 0;
}
//更新処理
void SceneObject::Update()
{
#pragma region  SceneObject操作
	randomVertex = easeOut(Vector3(-50, -50, -50),Vector3(), titleCount / 60.0f);
	position = Vector3();
#pragma endregion
	//Title
	titleObject->SetPosition(position);
	titleObject->SetRotation(rotation);
	titleObject->SetScale(scale);
	titleObject->SetRandomVertex(randomVertex);
	titleObject->Update();
}

void SceneObject::Draw(DirectXCommon* dxCommon)
{
	//Titleオブジェクト
	titleObject->Draw(dxCommon->GetCommandList());
}

void SceneObject::PlayUpdate(Vector3 p, bool b)
{
	//ホバリングの幅
	float range = 7.0f;
	//ホバリングの速さ
	hobCount += 0.2f;
	//Lスティックオブジェクト
	UIObject->SetPosition(p + Vector3(0, 5, 0));
	UIObject->SetRotation(Vector3(30, 180, sin(hobCount) * range));
	UIObject->Update();

}

void SceneObject::PlayDraw(DirectXCommon* dxCommon)
{
	//Lスティックオブジェクト
	UIObject->Draw(dxCommon->GetCommandList());

}

void SceneObject::ClearUpdate(Vector3 p)
{
	//CLEARオブジェクト
	clearObject->SetPosition(p + Vector3(0, 0, 20));
	clearObject->SetScale(Vector3(30, 30, 1));
	clearObject->Update();
	//ボタンUIオブジェクト
	ButtonUpdate(p+Vector3(0,-5,20),Vector3(1,1,1));

}

void SceneObject::ClearDraw(DirectXCommon* dxCommon)
{
	//CLEARオブジェクト
	clearObject->Draw(dxCommon->GetCommandList());
	ButtonDraw(dxCommon);
}

void SceneObject::GameOverUpdate(Vector3 p)
{
	//GameOverオブジェクト
	goObject->Update();
	goObject->SetPosition(p + Vector3(0, 0, 20));
	goObject->SetScale(Vector3(30,30,1));

	//ボタンUIオブジェクト
	ButtonUpdate(p + Vector3(0, -5, 20),Vector3(1,1,1));

}

void SceneObject::GameOverDraw(DirectXCommon* dxCommon)
{
	//GameOverオブジェクト
	goObject->Draw(dxCommon->GetCommandList());
	//ボタンUIオブジェクト
	ButtonDraw(dxCommon);
}

void SceneObject::ButtonUpdate(Vector3 p,Vector3 scale)
{
	//ホバリングの幅
	float range = 0.1f;
	//ホバリングの速さ
	hobCount += 0.3f;
	//ボタンUIオブジェクト
	ButtonObject->SetPosition(p);
	ButtonObject->SetScale(scale + Vector3(sin(hobCount) * range, sin(hobCount) * range, sin(hobCount) * range));
	ButtonObject->Update();
}

void SceneObject::ButtonDraw(DirectXCommon* dxCommon)
{
	//ボタンUIオブジェクト
	ButtonObject->Draw(dxCommon->GetCommandList());
}

void SceneObject::BoradUpdate(Vector3 p, std::vector<Player*>player)
{
	//リンクオブジェクト
	linkObject->SetTarget(p);
	linkObject->Update();
	//ボタンUIオブジェクト
	buttonBorad->SetPosition(linkObject->GetLinkObject()[linkObject->GetLinkSize() - 1]->GetPosition());
	for (int i = 0; i < player.size(); i++)
	{
		//Playerが看板に触れたら
		if (SphereAndCapsule(player[i]->GetPosition(), player[i]->GetScale().x,
			buttonBorad->GetPosition() + Vector3(-5, 0, 0), buttonBorad->GetPosition() + Vector3(5, 0, 0), scale.x*2, player[i]->GetLiveFlag()))
		{
			//看板がなびく
			linkObject->GetLinkObject()[linkObject->GetLinkSize() - 1]->SetVelocity(player[i]->GetVelocity());
			//看板角度加算
			boradRotation -= player[i]->GetVelocity() * 10.0f;
		}
	}
#pragma region 看板の角度減衰


	float stiffness = 0.3f;	//戻る強さ
	float damping = 0.95f;	//反動の減衰
	float mass = 10.0f;		//重さ

	Vector3 force = Vector3(stiffness * (-boradRotation.x), stiffness * (-boradRotation.y), 0.0f);
	accel = force / mass;
	//移動量
	velocity = damping * (velocity + accel);
	boradRotation += velocity;
#pragma endregion
	buttonBorad->SetRotation(boradRotation);
	buttonBorad->Update();
}

void SceneObject::BroadDraw(DirectXCommon* dxCommon)
{
	//リンクオブジェクトの描画
	linkObject->Draw(dxCommon);
	//ボードオブジェクト描画
	buttonBorad->Draw(dxCommon->GetCommandList());
}
