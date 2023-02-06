#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"
#include "Scene/Actors/Actor.h"
#include "StateComponent.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"

void MoveScriptComponent::Initialize()
{
}

void MoveScriptComponent::Update()
{
	auto camera = actor->GetComponent<CameraComponent>();
	auto state = actor->GetComponent<StateComponent>();
	auto physics = actor->GetComponent<PhysicsComponent>();
	auto key = context->GetSubSystem<InputManager>();
	if (!camera || !state || !physics || !key) { assert(false); return; }	//�ٸ� ������Ʈ �� üũ

	physics->SetIsUpdate(true);	//���� �׽� ����

	D3DXVECTOR3 position = transform->GetPosition();

	switch (state->GetState())
	{
	case State::Idle: break;
	case State::Walk: 
	{
		if (state->GetIsMirroredAnimation() == false) position.x += speed;
		else position.x -= speed;
		break;
	}
	case State::Jump: 
	{
		position.y += (jump_speed - physics->GetGravity());

		if (key->IsHoldOrDown(DIK_D)) position.x += speed;
		if (key->IsHoldOrDown(DIK_A)) position.x -= speed;
		break;
	}
	case State::Run:
	{
		if (state->GetIsMirroredAnimation() == false) position.x += run_speed;
		else position.x -= run_speed;
		break;
	}
	case State::Fly: 
	{
		physics->SetIsUpdate(false);	//���� off
		position.y += 1;
		if (key->IsHoldOrDown(DIK_D)) position.x += speed * 0.5f;
		if (key->IsHoldOrDown(DIK_A)) position.x -= speed * 0.5f;
		break;
	}
	case State::OnAir: break;
	case State::Action: 												  	break;
	case State::Dead: 													break;
	}

	ClipActor(position);
	camera->SetCameraPosition(position);
	transform->SetPosition(position);
}

void MoveScriptComponent::Destroy()
{
}

void MoveScriptComponent::SetSceneSize(SceneSize scene_size)
{
	this->scene_size = scene_size;
}

void MoveScriptComponent::ClipActor(D3DXVECTOR3& position)
{
	if (scene_size.min_x > position.x) position.x = scene_size.min_x;
	if (scene_size.max_x < position.x) position.x = scene_size.max_x;
	if (scene_size.min_y > position.y) position.y = scene_size.min_y;
	if (scene_size.max_y < position.y) position.y = scene_size.max_y;
}
