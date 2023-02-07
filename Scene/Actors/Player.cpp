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

Player::Player(Context* const context)
	: Actor(context)
{
	SetActorType(ActorType::Player);
	AddComponents();
	AddAnimations();

	GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 80.0f, 1.0f));
	GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(30.0f, 100.0f, 1.0f));
}

void Player::AddComponents()
{
	AddComponent<CameraComponent>();
	AddComponent<PhysicsComponent>();
	AddComponent<StateComponent>();
	AddComponent<ColliderComponent>();
	AddComponent<MoveScriptComponent>();
	AddComponent<MeshRendererComponent>();
	AddComponent<AnimatorComponent>();
}

void Player::AddAnimations()
{
	auto animator = GetComponent<AnimatorComponent>();

	animator->AddAnimation("Assets/Animation/Kirby/Idle.xml");
	animator->AddAnimation("Assets/Animation/Kirby/OnAir.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Walk.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Fly.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Run.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Jump.xml");
	animator->AddAnimation("Assets/Animation/Kirby/Action1.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle");
}
