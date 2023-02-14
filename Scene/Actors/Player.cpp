#include "stdafx.h"
#include "Player.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/StateComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/PhysicsComponent.h"
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/ActionComponent.h"

Player::Player(Context* const context)
	: Actor(context)
{
	SetActorType(ActorType::Player);
	AddComponents();
	AddAnimations();

	GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
	GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f, 280.0f, 1.0f));
}

void Player::AddComponents()
{
	AddComponent<CameraComponent>();
	AddComponent<PhysicsComponent>();
	AddComponent<StateComponent>();
	AddComponent<ColliderComponent>();
	AddComponent<ActionComponent>();
	AddComponent<MoveScriptComponent>();
	AddComponent<MeshRendererComponent>();
	AddComponent<AnimatorComponent>();
}

void Player::AddAnimations()
{
	auto animator = GetComponent<AnimatorComponent>();

	//hungry
	animator->AddAnimation("Assets/Animation/Kirby/Idle.xml");
	animator->AddAnimation("Assets/Animation/Kirby/OnAir.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Walk.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fly.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Run.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Jump.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Action1.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Damaged.xml");

	//full
	animator->AddAnimation("Assets/Animation/Kirby/Full/Full_Idle.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Full/Full_OnAir.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Full/Full_Walk.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Full/Full_Jump.xml");

	//fire
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_Idle.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_Walk.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_Jump.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_Fly.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_Run.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_OnAir.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_Damaged.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fire/Fire_Attack.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle");
}
