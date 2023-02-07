#include "stdafx.h"
#include "Scene_1_3.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Actors/Monster.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/StateComponent.h"
#include "Scene/Component/MaterialRendererComponent.h"
#include "Scene/Component/BackGroundComponent.h"
#include "Scene/Component/PhysicsComponent.h"
#include "Scene/Component/AiScriptBasicComponent.h"
#include "Scene/Component/SceneChangeComponent.h"

void Scene_1_3::Init()
{
	//배경
	auto back_ground = AddBackGround("BackGround_Forest.png");

	//문
	auto door = AddDoor("Door.png", scene_size.max_x - 50.0f, 160.0f);
	auto scene_change = door->AddComponent<SceneChangeComponent>();

	//맵 타일
	std::shared_ptr<Actor> map_tiles[60];

	for (int i = 0; i < 60; i++)
	{
		map_tiles[i] = CreateActor();
		map_tiles[i]->SetActorType(ActorType::MapTile);
		map_tiles[i]->AddComponent<MeshRendererComponent>();
		map_tiles[i]->AddComponent<MaterialRendererComponent>();
	}

	for (int i = 0; i < 40; i++)	//맵 위치 세팅
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 30.0f, 1.0f));
	}

	for (int i = 40; i < 60; i++)	//맵 위치 세팅
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 40), 90.0f, 1.0f));
	}

	//몬스터1
	std::shared_ptr<Actor> monster = std::make_shared<Monster>(context);
	auto ai_move = monster->AddComponent<AiScriptBasicComponent>();
	ai_move->SetMinMaxX(1300, 1900);

	AddActor(monster);

	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 80.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1300.0f, 160.0f, 1.0f));

	//몬스터2
	std::shared_ptr<Actor> monster_ice = std::make_shared<Monster>(context);
	std::static_pointer_cast<Monster>(monster_ice)->SetAttribute(Monster_Attribute::Ice);
	auto ai_move_ice = monster_ice->AddComponent<AiScriptBasicComponent>();
	ai_move_ice->SetMinMaxX(300, 900);

	AddActor(monster_ice);

	monster_ice->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 80.0f, 1.0f));
	monster_ice->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(400.0f, 100.0f, 1.0f));

	//플레이어
	AddActor(player);
}
