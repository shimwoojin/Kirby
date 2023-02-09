#include "stdafx.h"
#include "Scene_1_5.h"
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
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/AiScriptBossComponent.h"

Scene_1_5::Scene_1_5(Context* const context)
	: Scene(context)
{
	uint width = static_cast<uint>(Settings::Get().GetWidth());
	uint height = static_cast<uint>(Settings::Get().GetHeight());

	scene_size = { 0, width, 0, height };
}

void Scene_1_5::Init()
{
	//배경
	auto back_ground = AddBackGround("BackGround_Forest.png");

	//문
	auto door = AddDoor("Door.png", scene_size.max_x + 250.0f, 160.0f);
	auto scene_change = door->AddComponent<SceneChangeComponent>();

	//맵 타일
	std::shared_ptr<Actor> map_tiles[30];

	for (int i = 0; i < 30; i++)
	{
		map_tiles[i] = CreateActor();
		map_tiles[i]->SetActorType(ActorType::MapTile);
		map_tiles[i]->AddComponent<MeshRendererComponent>();
		map_tiles[i]->AddComponent<MaterialRendererComponent>();
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	}

	for (int i = 0; i < 20; i++)	map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 30.0f, 1.0f));
	for (int i = 20; i < 25; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 20), 290.0f, 1.0f));
	for (int i = 25; i < 30; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(750.0f + 60.0f * (i - 25), 490.0f, 1.0f));

	//보스몹
	std::shared_ptr<Actor> boss = std::make_shared<Monster>(context);
	std::static_pointer_cast<Monster>(boss)->SetIsBoss(true);
	std::static_pointer_cast<Monster>(boss)->SetHp(2500.0f);
	auto physics = boss->AddComponent<PhysicsComponent>();
	physics->SetScene(this);
	auto ai_move = boss->AddComponent<AiScriptBasicComponent>();
	ai_move->SetMinMaxX(150, 900);
	auto ai_boss = boss->AddComponent<AiScriptBossComponent>();

	boss->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(200.0f, 200.0f, 1.0f));
	boss->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(700.0f, 300.0f, 1.0f));

	AddActor(boss);

	//플레이어
	AddActor(player);
	AddActor(weapon);
}
