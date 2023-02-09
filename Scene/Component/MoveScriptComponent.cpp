#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"
#include "Scene/Actors/Actor.h"
#include "StateComponent.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "ActionComponent.h"

void MoveScriptComponent::Initialize()
{
}

void MoveScriptComponent::Update()
{
	auto camera = actor->GetComponent<CameraComponent>();
	auto state = actor->GetComponent<StateComponent>();
	auto physics = actor->GetComponent<PhysicsComponent>();
	auto collider = actor->GetComponent<ColliderComponent>();
	auto action = actor->GetComponent<ActionComponent>();
	auto key = context->GetSubSystem<InputManager>();

	if (!camera || !state || !physics || !collider || !action || !key) 
	{
		assert(false); return; //다른 컴포넌트 널 체크
	}	

	physics->SetIsUpdate(true);	//물리 항시 적용
	action->SetIsUpdate(false);		//액션일때만 on
	collider->SetIsUpdate(true);	//몬스터 충돌 체크, 충돌 시 충돌 체크 off -> 무적상태(약 0.6초)

	D3DXVECTOR3 position = transform->GetPosition();

	switch (state->GetState())
	{
	case State::Idle: break;
	case State::Walk: 
	{
		if (key->IsHoldOrDown(DIK_D) && collider->IsCollideRightTile() == false) position.x += speed;
		if (key->IsHoldOrDown(DIK_A) && collider->IsCollideLeftTile() == false) position.x -= speed;
		break;
	}
	case State::Jump: 
	{
		position.y += (jump_speed - physics->GetGravity());

		if (key->IsHoldOrDown(DIK_D) && collider->IsCollideRightTile() == false) position.x += speed;
		if (key->IsHoldOrDown(DIK_A) && collider->IsCollideLeftTile() == false) position.x -= speed;
		break;
	}
	case State::Run:
	{
		if (key->IsHoldOrDown(DIK_D) && collider->IsCollideRightTile() == false) position.x += run_speed;
		if (key->IsHoldOrDown(DIK_A) && collider->IsCollideLeftTile() == false) position.x -= run_speed;
		break;
	}
	case State::Fly: 
	{
		physics->SetIsUpdate(false);	//물리 off

		if(collider->IsCollideUpTile() == false) position.y += 1;

		if (key->IsHoldOrDown(DIK_D) && collider->IsCollideRightTile() == false) position.x += speed * 0.5f;
		if (key->IsHoldOrDown(DIK_A) && collider->IsCollideLeftTile() == false) position.x -= speed * 0.5f;
		break;
	}
	case State::OnAir: 
	{
		if (key->IsHoldOrDown(DIK_D) && collider->IsCollideRightTile() == false) position.x += speed * 0.5f;
		if (key->IsHoldOrDown(DIK_A) && collider->IsCollideLeftTile() == false) position.x -= speed * 0.5f;
		break;
	}
	case State::Action:
	{
		action->SetIsUpdate(true);
		break;
	}
	case State::Attack:
	{
		action->SetIsUpdate(true);
		break;
	}
	case State::Damaged:
	{
		collider->SetIsUpdate(false);
		if (collider->IsCollideRightMonster() == true) position.x -= 0.5f;
		if (collider->IsCollideLeftMonster() == true) position.x += 0.5f;
		break;
	}
	case State::Dead:
	{

		break;
	}

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
