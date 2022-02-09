#include "GameObject.h"
SoundManager* GameObject::soundManager = nullptr;
Input* GameObject::input = nullptr;
Xinput* GameObject::pad = nullptr;
Loader* GameObject::modelLoader = nullptr;


GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

void GameObject::SetAssets(SoundManager* s, Input* i, Xinput* x)
{
	soundManager = s;
	input = i;
	pad = x;
}

