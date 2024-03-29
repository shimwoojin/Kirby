#include "stdafx.h"
#include "Scene.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Actors/Player.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/StateComponent.h"
#include "Scene/Component/MaterialRendererComponent.h"
#include "Scene/Component/BackGroundComponent.h"
#include "Scene/Component/PhysicsComponent.h"
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/SceneChangeComponent.h"
#include "Scene/Component/ActionComponent.h"

std::shared_ptr<Actor> Scene::player = nullptr;
std::shared_ptr<Actor> Scene::weapon = nullptr;

Scene::Scene(class Context* const context)
	:context(context)
{
	renderer = context->GetSubSystem<Renderer>();

	//scene 사이즈 기본 값
	uint width = static_cast<uint>(Settings::Get().GetWidth() * 2);
	uint height = static_cast<uint>(Settings::Get().GetHeight() * 1.5);
	scene_size = { 0, width, 0, height};

	//player 늦은 초기화
	if (player == nullptr) player = std::make_shared<Player>(context);

	//weapon 늦은 초기화 + player와 부모, 자식 설정
	if (weapon == nullptr)
	{
		weapon = std::make_shared<Actor>(context);
		weapon->SetActorType(ActorType::Weapon);
		weapon->AddComponent<MeshRendererComponent>();
		auto animator = weapon->AddComponent<AnimatorComponent>();

		animator->AddAnimation("Assets/Animation/Kirby/Weapon/Weapon_Swallow.xml");
		animator->AddAnimation("Assets/Animation/Kirby/Weapon/Weapon_Fire.xml");
		animator->SetAnimationMode(AnimationMode::Play);
		animator->SetCurrentAnimation("Weapon_Swallow");

		weapon->GetComponent<TransformComponent>()->SetParent(player->GetTransform());
		player->GetTransform()->AddChild(weapon->GetTransform());

		weapon->GetTransform()->SetLocalPosition(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		weapon->GetTransform()->SetScale(D3DXVECTOR3(20.0f, 100.0f, 1.0f));
	}
}

Scene::~Scene()
{
}

void Scene::Update()
{
	//===================================================
	// [프레임 제한]
	//===================================================
	//static auto timer = context->GetSubSystem<Timer>();
	//static float delta_time = 0.0f;
	//delta_time += timer->GetDeltaTimeMS();
	//if (delta_time > (1000 / FPS))
	//{
	//	delta_time = 0.0f;
	//	return;
	//}
	//===================================================
	// [Scene Update]
	//===================================================
	
	if (scene_change == true)
	{
		player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f, 280.0f, 1.0f));		//플레이어 위치

		player->GetComponent<MoveScriptComponent>()->SetSceneSize(scene_size);	//update
		player->GetComponent<ActionComponent>()->SetScene(this);//update
		auto physics = player->GetComponent<PhysicsComponent>();//update
		physics->SetScene(this);//update
		auto camera = player->GetComponent<CameraComponent>();//update
		camera->SetScene(this);//update
		auto collider = player->GetComponent<ColliderComponent>();//update
		collider->SetScene(this);//update
		actors[0]->GetComponent<BackGroundComponent>()->SetCamera(camera.get());	//배경 update
		actors[1]->GetComponent<SceneChangeComponent>()->SetScene(this);			//문 update

		renderer->UpdateRenderables(this);	//scene이 바뀌면 렌더 목록 업데이트

		scene_change = false;
	}

	if (is_update == true)
	{
		renderer->UpdateRenderables(this);	//액터가 추가되거나 만들어지면 렌더 목록 업데이트
		is_update = false;
	}

	for (const auto& actor : actors)
		actor->Update();
}

const std::shared_ptr<class Actor> Scene::CreateActor(const bool& is_active)
{
	is_update = true;
	std::shared_ptr<Actor> actor = std::make_shared<Actor>(context);

	actor->SetActive(is_active);
	AddActor(actor);

	return actor;
}

void Scene::AddActor(const std::shared_ptr<class Actor>& actor)
{
	is_update = true;
	actors.emplace_back(actor);
}

std::shared_ptr<class Actor> Scene::AddBackGround(std::string path)
{
	//배경
	std::shared_ptr<Actor> back_ground = CreateActor();
	back_ground->SetActorType(ActorType::BackGround);
	back_ground->AddComponent<MeshRendererComponent>();
	auto MRC = back_ground->AddComponent<MaterialRendererComponent>();
	back_ground->AddComponent<BackGroundComponent>();

	MRC->SetTexture2D("./Assets/Texture/Background/" + path);
	back_ground->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(Settings::Get().GetWidth(), Settings::Get().GetHeight(), 1));

	return back_ground;
}

std::shared_ptr<class Actor> Scene::AddDoor(std::string path, float x, float y)
{
	std::shared_ptr<Actor> door = CreateActor();
	door->SetActorType(ActorType::Door);
	door->AddComponent<MeshRendererComponent>();
	auto door_image = door->AddComponent<MaterialRendererComponent>();
	door_image->SetTexture2D("./Assets/Texture/Maps/" + path);
	door->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(80.0f, 80.0f, 1.0f));

	door->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(x, y, 1.0f));

	return door;
}
