#include "stdafx.h"
#include "Scene_1_2.h"
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

void Scene_1_2::Init()
{
	//πË∞Ê
	auto back_ground = AddBackGround("BackGround_Forest2.png");

	//πÆ
	auto door = AddDoor("Door.png", scene_size.max_x - 50.0f, 460.0f);
	auto scene_change = door->AddComponent<SceneChangeComponent>();

	//∏  ≈∏¿œ
	AddMapTile();

	//∏ÛΩ∫≈Õ1
	std::shared_ptr<Actor> monster = std::make_shared<Monster>(context);
	auto ai_move = monster->AddComponent<AiScriptBasicComponent>();
	ai_move->SetMinMaxX(1500, 1800);
	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1500.0f, 450.0f, 1.0f));

	AddActor(monster);


	//∏ÛΩ∫≈Õ2
	std::shared_ptr<Actor> monster_fire = std::make_shared<Monster>(context);
	std::static_pointer_cast<Monster>(monster_fire)->SetAttribute(Monster_Attribute::Fire);
	auto ai_move_fire = monster_fire->AddComponent<AiScriptBasicComponent>();
	ai_move_fire->SetMinMaxX(500, 800);

	AddActor(monster_fire);

	monster_fire->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	monster_fire->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(400.0f, 690.0f, 1.0f));

	//«√∑π¿ÃæÓ
	AddActor(player);
	AddActor(weapon);
}

void Scene_1_2::AddMapTile()
{
	//∏  ≈∏¿œ
	std::shared_ptr<Actor> map_tiles[210];

	for (int i = 0; i < 210; i++)
	{
		map_tiles[i] = CreateActor();
		map_tiles[i]->SetActorType(ActorType::MapTile);
		map_tiles[i]->AddComponent<MeshRendererComponent>();
		map_tiles[i]->AddComponent<MaterialRendererComponent>();
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	}

	for (int i = 0; i < 40; i++)	//1√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 30.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 40; i < 80; i++)	//2√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 40), 90.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 80; i < 100; i++)	//3√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * (i - 80), 150.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass.png");
	}
	for (int i = 100; i < 120; i++)	//3√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 100), 150.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 120; i < 140; i++)	//3√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 120), 210.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 140; i < 160; i++)	//4√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 140), 270.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 160; i < 180; i++)	//5√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 160), 330.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass_Under.png");
	}
	for (int i = 180; i < 200; i++)	//6√˛
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 180), 390.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Grass.png");
	}
	for (int i = 200; i < 210; i++)	
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(450.0f + 60.0f * (i - 200), 630.0f, 1.0f));
		map_tiles[i]->GetComponent<MaterialRendererComponent>()->SetTexture2D("./Assets/Texture/Maps/MapTile_Dessert.png");
	}
}
