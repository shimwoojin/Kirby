#include "stdafx.h"
#include "Scene_1_4.h"
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
#include "Scene/Component/SceneChangeComponent.h"

Scene_1_4::Scene_1_4(Context* const context)
	: Scene(context)
{
	uint width = static_cast<uint>(Settings::Get().GetWidth());
	uint height = static_cast<uint>(Settings::Get().GetHeight() * 3);

	scene_size = { 0, width, 0, height };
}

void Scene_1_4::Init()
{
	//배경
	auto back_ground = AddBackGround("BackGround_Forest.png");

	//문
	auto door = AddDoor("Door.png", scene_size.max_x - 50.0f, 1660.0f);
	auto scene_change = door->AddComponent<SceneChangeComponent>();

	//맵 타일
	std::shared_ptr<Actor> map_tiles[70];

	for (int i = 0; i < 70; i++)
	{
		map_tiles[i] = CreateActor();
		map_tiles[i]->SetActorType(ActorType::MapTile);
		map_tiles[i]->AddComponent<MeshRendererComponent>();
		map_tiles[i]->AddComponent<MaterialRendererComponent>();
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	}

	//타일 위치
	for (int i = 0; i < 20; i++)	map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 30.0f, 1.0f));
	for(int i = 20; i < 23; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(290.0f + 60.0f * (i - 20), 150.0f, 1.0f));
	for(int i = 23; i < 26; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 23), 270.0f, 1.0f));
	for(int i = 26; i < 29; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(290.0f + 60.0f * (i - 26), 390.0f, 1.0f));
	for(int i = 29; i < 32; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 29), 510.0f, 1.0f));
	for(int i = 32; i < 35; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(290.0f + 60.0f * (i - 32), 630.0f, 1.0f));
	for(int i = 35; i < 38; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 35), 750.0f, 1.0f));
	for(int i = 38; i < 41; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(290.0f + 60.0f * (i - 38), 870.0f, 1.0f));
	for(int i = 41; i < 44; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 41), 990.0f, 1.0f));
	for(int i = 44; i < 47; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(290.0f + 60.0f * (i - 44), 1110.0f, 1.0f));
	for(int i = 47; i < 50; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 47), 1230.0f, 1.0f));
	for(int i = 50; i < 53; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(290.0f + 60.0f * (i - 50), 1350.0f, 1.0f));
	for(int i = 53; i < 56; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 53), 1470.0f, 1.0f));
	for(int i = 56; i < 70; i++) map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(290.0f + 60.0f * (i - 56), 1590.0f, 1.0f));

	//플레이어
	AddActor(player);


	//몬스터
	std::shared_ptr<Actor> monster = std::make_shared<Monster>(context);
	auto ai_move = monster->AddComponent<AiScriptBasicComponent>();
	ai_move->SetMinMaxX(300, 900);
	
	AddActor(monster);
	
	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(400.0f, 90.0f, 1.0f));
}
