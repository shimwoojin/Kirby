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

Scene_1_3::Scene_1_3(Context* const context)
	: Scene(context)
{
	uint width = static_cast<uint>(Settings::Get().GetWidth() * 6);
	uint height = static_cast<uint>(Settings::Get().GetHeight());

	scene_size = { 0, width, 0, height };
}

void Scene_1_3::Init()
{
	//¹è°æ
	auto back_ground = AddBackGround("BackGround_Forest2.png");

	//¹®
	auto door = AddDoor("Door.png", scene_size.max_x - 50.0f, 220.0f);
	auto scene_change = door->AddComponent<SceneChangeComponent>();

	//¸Ê Å¸ÀÏ
	AddMapTile();

	//¸ó½ºÅÍ1
	std::shared_ptr<Actor> monster = std::make_shared<Monster>(context);
	auto ai_move = monster->AddComponent<AiScriptBasicComponent>();
	ai_move->SetMinMaxX(1500, 2000);
	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1500.0f, 210.0f, 1.0f));
	AddActor(monster);

	//¸ó½ºÅÍ2
	std::shared_ptr<Actor> monster2 = std::make_shared<Monster>(context);
	std::static_pointer_cast<Monster>(monster2)->SetAttribute(Monster_Attribute::Ice);
	auto ai_move2 = monster2->AddComponent<AiScriptBasicComponent>();
	ai_move2->SetMinMaxX(500, 1000);
	monster2->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster2->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(500.0f, 210.0f, 1.0f));
	AddActor(monster2);

	//¸ó½ºÅÍ3
	std::shared_ptr<Actor> monster3 = std::make_shared<Monster>(context);
	std::static_pointer_cast<Monster>(monster3)->SetAttribute(Monster_Attribute::Fire);
	auto ai_move3 = monster3->AddComponent<AiScriptBasicComponent>();
	ai_move3->SetMinMaxX(2500, 3000);
	monster3->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster3->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(2500.0f, 210.0f, 1.0f));
	AddActor(monster3);

	//¸ó½ºÅÍ4
	std::shared_ptr<Actor> monster4 = std::make_shared<Monster>(context);
	auto ai_move4 = monster4->AddComponent<AiScriptBasicComponent>();
	ai_move4->SetMinMaxX(3500, 4000);
	monster4->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster4->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(3500.0f, 210.0f, 1.0f));
	AddActor(monster4);

	//¸ó½ºÅÍ5
	std::shared_ptr<Actor> monster5 = std::make_shared<Monster>(context);
	std::static_pointer_cast<Monster>(monster5)->SetAttribute(Monster_Attribute::Ice);
	auto ai_move5 = monster5->AddComponent<AiScriptBasicComponent>();
	ai_move5->SetMinMaxX(4500, 5000);
	monster5->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster5->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(4500.0f, 210.0f, 1.0f));
	AddActor(monster5);

	//¸ó½ºÅÍ6
	std::shared_ptr<Actor> monster6 = std::make_shared<Monster>(context);
	std::static_pointer_cast<Monster>(monster6)->SetAttribute(Monster_Attribute::Fire);
	auto ai_move6 = monster6->AddComponent<AiScriptBasicComponent>();
	ai_move6->SetMinMaxX(5500, 6000);
	monster6->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster6->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(5500.0f, 210.0f, 1.0f));
	AddActor(monster6);


	//ÇÃ·¹ÀÌ¾î
	AddActor(player);
	AddActor(weapon);
}

void Scene_1_3::AddMapTile()
{
	//¸Ê Å¸ÀÏ
	std::shared_ptr<Actor> map_tiles[309];

	for (int i = 0; i < 309; i++)
	{
		map_tiles[i] = CreateActor();
		map_tiles[i]->SetActorType(ActorType::MapTile);
		map_tiles[i]->AddComponent<MeshRendererComponent>();
		map_tiles[i]->AddComponent<MaterialRendererComponent>();
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	}

	for (int i = 0; i < 103; i++)	//1Ãþ
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 30.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 103; i < 206; i++)	//2Ãþ
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 103), 90.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 206; i < 309; i++)	//3Ãþ
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 206), 150.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass.png");
	}
}
