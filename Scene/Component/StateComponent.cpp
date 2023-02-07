#include "stdafx.h"
#include "StateComponent.h"
#include "AnimatorComponent.h"
#include "PhysicsComponent.h"
#include "AiScriptBasicComponent.h"
#include "ColliderComponent.h"
#include "Scene/Actors/Actor.h"

void StateComponent::Initialize()
{
	key = context->GetSubSystem<InputManager>();
	physics = actor->GetComponent<PhysicsComponent>();
	collider = actor->GetComponent<ColliderComponent>();
}

void StateComponent::Update()
{
	auto type = actor->GetActorType();

	if (type == ActorType::Player) UpdateActor();
	else if (type == ActorType::Monster) UpdateMonster();
	else return;
}

void StateComponent::Destroy()
{
}

void StateComponent::UpdateActor()
{
	switch (state)
	{
	case State::Idle:
	{
		if (key->IsHoldOrDown(DIK_D))
		{
			state = State::Walk;
			is_mirrored_animation = false;
			if (key->IsHoldOrDown(DIK_LSHIFT)) state = State::Run;
		}
		else if (key->IsHoldOrDown(DIK_A))
		{
			state = State::Walk;
			is_mirrored_animation = true;
			if (key->IsHoldOrDown(DIK_LSHIFT)) state = State::Run;
		}
		else if (key->IsHoldOrDown(DIK_SPACE))
		{
			state = State::Fly;
		}
		else if (key->IsDown(DIK_W) && physics->IsOnGround())
		{
			state = State::Jump;
		}
		else if (key->IsMouseRButtonHoldOrDown())
		{
			state = State::Action;
		}
		else state = State::Idle;
	}
	break;
	case State::Walk:
	{
		if (key->IsHoldOrDown(DIK_W) && physics->IsOnGround())
		{
			state = State::Jump;
		}
		else if (key->IsHoldOrDown(DIK_SPACE))
		{
			state = State::Fly;
		}
		else if (key->IsMouseRButtonHoldOrDown())
		{
			state = State::Action;
		}
		else if (key->IsHoldOrDown(DIK_D))
		{
			is_mirrored_animation = false;
			if (key->IsHoldOrDown(DIK_LSHIFT)) state = State::Run;
			if (key->IsHoldOrDown(DIK_W) && physics->IsOnGround()) state = State::Jump;
		}
		else if (key->IsHoldOrDown(DIK_A))
		{
			is_mirrored_animation = true;
			if (key->IsHoldOrDown(DIK_LSHIFT)) state = State::Run;
			if (key->IsHoldOrDown(DIK_W) && physics->IsOnGround()) state = State::Jump;
		}
		else state = State::Idle;
	}
	break;
	case State::Run:
	{
		if (key->IsHoldOrDown(DIK_D) && key->IsHoldOrDown(DIK_LSHIFT))
		{
			is_mirrored_animation = false;
		}
		else if (key->IsHoldOrDown(DIK_A) && key->IsHoldOrDown(DIK_LSHIFT))
		{
			is_mirrored_animation = true;
		}
		else state = State::Idle;
	}
	break;
	case State::Jump:
	{
		if (key->IsDown(DIK_SPACE))
		{
			state = State::OnAir;
		}
		else if (physics->IsOnGround() == false)	//else의 바로 위
		{
			state = State::Jump;
		}
		else
		{
			state = State::Idle;
		}
	}
	break;
	case State::OnAir:
	{
		if (key->IsHoldOrDown(DIK_SPACE))
		{
			state = State::Fly;
			physics->SetGravity(0.0f);
		}
		else if (physics->IsOnGround() == false)
		{
			if (key->IsHoldOrDown(DIK_D))
			{
				is_mirrored_animation = false;
			}
			else if (key->IsHoldOrDown(DIK_A))
			{
				is_mirrored_animation = true;
			}
		}
		else state = State::Idle;

		break;
	}

	case State::Fly:
	{
		if (key->IsHold(DIK_SPACE))
		{
			if (key->IsHoldOrDown(DIK_D))
			{
				is_mirrored_animation = false;
			}
			else if (key->IsHoldOrDown(DIK_A))
			{
				is_mirrored_animation = true;
			}
		}
		else
			state = State::OnAir;
	}
	break;
	case State::Action:
	{
		if (key->IsMouseRButtonHoldOrDown())
		{
			state = State::Action;
		}
		else 
			state = State::Idle;
	}
		break;
	case State::Damaged:
		break;
	case State::Dead:
		break;
	}
}

void StateComponent::UpdateMonster()
{
	auto AiScript = actor->GetComponent<AiScriptBasicComponent>();

	switch (state)
	{
	case State::Idle:
		break;
	case State::Walk:
	{
		if (AiScript->GetIsRight() == true) is_mirrored_animation = true;
		else is_mirrored_animation = false;
	}
		break;
	case State::Run:
		break;
	case State::Action:
		break;
	case State::Damaged:
		break;
	case State::Dead:
		break;
	}
}
