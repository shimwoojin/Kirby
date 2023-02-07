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

Scene_1_1::Scene_1_1(Context* const context)
	: Scene(context)
{
}

void Scene_1_1::Init()
{
	//��� -> 0�� ���� ����
	auto back_ground = AddBackGround("BackGround_Forest.png");

	//�� -> 1�� ���� ����
	auto door = AddDoor("Door.png", scene_size.max_x - 50.0f, 160.0f);
	auto scene_change = door->AddComponent<SceneChangeComponent>();

	//�� Ÿ��
	std::shared_ptr<Actor> map_tiles[60];

	for (int i = 0; i < 60; i++)
	{
		map_tiles[i] = CreateActor();
		map_tiles[i]->SetActorType(ActorType::MapTile);
		map_tiles[i]->AddComponent<MeshRendererComponent>();
		map_tiles[i]->AddComponent<MaterialRendererComponent>();
	}

	for (int i = 0; i < 40; i++)	//�� ��ġ ����
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f + 60.0f * i, 30.0f, 1.0f));
	}

	for (int i = 40; i < 60; i++)	//�� ��ġ ����
	{
		map_tiles[i]->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
		map_tiles[i]->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(1230.0f + 60.0f * (i - 40), 90.0f, 1.0f));
	}

	//�÷��̾�
	AddActor(player);
	

	//����
	std::shared_ptr<Actor> monster = std::make_shared<Monster>(context);
	auto ai_move = monster->AddComponent<AiScriptBasicComponent>();
	ai_move->SetMinMaxX(300, 900);

	AddActor(monster);

	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 80.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(400.0f, 100.0f, 1.0f));

	//ȭ�� ��ȯ �� ������Ʈ �ؾ� �� �׸��
	player->GetComponent<MoveScriptComponent>()->SetSceneSize(scene_size);	//update
	auto physics = player->GetComponent<PhysicsComponent>();//update
	physics->SetScene(this);//update
	auto camera = player->GetComponent<CameraComponent>();//update
	camera->SetScene(this);//update
	auto collider = player->GetComponent<ColliderComponent>();//update
	collider->SetScene(this);//update
	scene_change->SetScene(this);
	back_ground->GetComponent<BackGroundComponent>()->SetCamera(camera.get());//update
}
