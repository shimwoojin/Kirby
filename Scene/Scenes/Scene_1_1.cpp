#include "stdafx.h"
#include "Scene_1_1.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Actors/Player.h"
#include "Scene/Actors/Monster.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/StateComponent.h"
#include "Scene/Component/MaterialRendererComponent.h"
#include "Scene/Component/BackGroundComponent.h"
#include "Scene/Component/AiScriptBasicComponent.h"
#include "Scene/Component/PhysicsComponent.h"
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/SceneChangeComponent.h"
#include "Scene/Component/ActionComponent.h"

Scene_1_1::Scene_1_1(Context* const context)
	: Scene(context)
{
}

void Scene_1_1::Init()
{
	//배경 -> 0번 액터 고정
	auto back_ground = AddBackGround("BackGround_Forest2.png");

	//문 -> 1번 액터 고정
	auto door = AddDoor("Door.png", scene_size.max_x - 50.0f, 280.0f);
	auto scene_change = door->AddComponent<SceneChangeComponent>();

	//맵타일
	AddMapTile();

	//몬스터
	std::shared_ptr<Actor> monster = std::make_shared<Monster>(context);
	auto ai_move = monster->AddComponent<AiScriptBasicComponent>();
	ai_move->SetMinMaxX(300, 900);

	AddActor(monster);

	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(400.0f, 210.0f, 1.0f));

	//플레이어, 웨폰
	AddActor(player);
	AddActor(weapon);

	//화면 전환 시 업데이트 해야 할 항목들
	player->GetComponent<MoveScriptComponent>()->SetSceneSize(scene_size);	//update
	player->GetComponent<ActionComponent>()->SetScene(this);
	auto physics = player->GetComponent<PhysicsComponent>();//update
	physics->SetScene(this);//update
	auto camera = player->GetComponent<CameraComponent>();//update
	camera->SetScene(this);//update
	auto collider = player->GetComponent<ColliderComponent>();//update
	collider->SetScene(this);//update
	scene_change->SetScene(this);
	back_ground->GetComponent<BackGroundComponent>()->SetCamera(camera.get());//update
}

void Scene_1_1::AddMapTile()
{
	//맵 타일
	std::shared_ptr<Actor> map_tiles[140];

	for (int i = 0; i < 140; i++)
	{
		map_tiles[i] = CreateActor();
		map_tiles[i]->SetActorType(ActorType::MapTile);
		map_tiles[i]->AddComponent<MeshRendererComponent>();
		map_tiles[i]->AddComponent<MaterialRendererComponent>();
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	}

	for (int i = 0; i < 20; i++)
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 150.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass.png");
	}
	for (int i = 20; i < 40; i++)
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 150.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 40; i < 60; i++)
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 40), 210.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass.png");
	}
	for (int i = 60; i < 100; i++)
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 60), 90.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 100; i < 140; i++)
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 100), 30.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
}
