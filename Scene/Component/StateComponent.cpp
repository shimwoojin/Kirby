#include "stdafx.h"
#include "StateComponent.h"
#include "AnimatorComponent.h"
#include "PhysicsComponent.h"
#include "AiScriptBasicComponent.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Actors/Player.h"

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
	else if (type == ActorType::Monster && static_cast<Monster*>(actor)->GetIsBoss() == false) UpdateMonster();
	else if (type == ActorType::Monster && static_cast<Monster*>(actor)->GetIsBoss() == true) UpdateBoss();
	else return;
}

void StateComponent::Destroy()
{
}

void StateComponent::UpdateActor()
{
	auto kirby_state = static_cast<Player*>(actor)->GetKirbyState();
	auto animator = actor->GetComponent<AnimatorComponent>();

	static float attack_limit_time = 0.0f;

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
		else if (key->IsHoldOrDown(DIK_SPACE) && kirby_state != KirbyState::Full)
		{
			state = State::Fly;
		}
		else if (key->IsDown(DIK_W) && physics->IsOnGround())
		{
			state = State::Jump;
		}
		else if (key->IsMouseRButtonHoldOrDown() && kirby_state == KirbyState::Hungry)
		{
			state = State::Action;
		}
		else if (key->IsMouseRButtonDown() && kirby_state == KirbyState::Full)
		{
			static_cast<Player*>(actor)->SetKirbyState(KirbyState::Hungry);
			state = State::Idle;
		}
		else if (key->IsDown(DIK_S) && kirby_state == KirbyState::Full)
		{
			auto kirby_eaten = static_cast<Player*>(actor)->GetKirbyEaten();
			if(kirby_eaten == Monster_Attribute::None)
			{
				static_cast<Player*>(actor)->SetKirbyState(KirbyState::Hungry);
				actor->GetTransform()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
				state = State::Idle;
			}
			else if (kirby_eaten == Monster_Attribute::Fire)
			{
				static_cast<Player*>(actor)->SetKirbyState(KirbyState::Fire);
				static_cast<Player*>(actor)->SetKirbyEaten(Monster_Attribute::None);
				actor->GetTransform()->SetScale(D3DXVECTOR3(60.0f, 80.0f, 1.0f));
				auto position = actor->GetTransform()->GetPosition();
				position.y += 10.0f;
				actor->GetTransform()->SetPosition(position);
				state = State::Idle;
			}
			else if (kirby_eaten == Monster_Attribute::Ice)
			{
				static_cast<Player*>(actor)->SetKirbyState(KirbyState::Fire);
				static_cast<Player*>(actor)->SetKirbyEaten(Monster_Attribute::None);
				actor->GetTransform()->SetScale(D3DXVECTOR3(60.0f, 80.0f, 1.0f));
				auto position = actor->GetTransform()->GetPosition();
				position.y += 10.0f;
				actor->GetTransform()->SetPosition(position);
				state = State::Idle;
			}
			state = State::Idle;
		}
		else if (key->IsDown(DIK_1))
		{
			static_cast<Player*>(actor)->SetKirbyState(KirbyState::Hungry);
			actor->GetTransform()->SetScale(D3DXVECTOR3(60.0f, 60.0f, 1.0f));
			state = State::Idle;
		}
		else if (key->IsMouseLButtonHoldOrDown() && kirby_state != KirbyState::Hungry && kirby_state != KirbyState::Full)
		{
			attack_limit_time += context->GetSubSystem<Timer>()->GetDeltaTimeMS();
			if(attack_limit_time > 100.0f) state = State::Attack;
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
		else if (key->IsHoldOrDown(DIK_SPACE) && kirby_state != KirbyState::Full)
		{
			state = State::Fly;
		}
		else if (key->IsMouseRButtonHoldOrDown() && kirby_state == KirbyState::Hungry)
		{
			state = State::Action;
		}
		else if (key->IsMouseLButtonHoldOrDown() && kirby_state != KirbyState::Hungry && kirby_state != KirbyState::Full)
		{
			state = State::Attack;
		}
		else if (key->IsHoldOrDown(DIK_D))
		{
			is_mirrored_animation = false;
			if (key->IsHoldOrDown(DIK_LSHIFT) && kirby_state != KirbyState::Full) state = State::Run;
			if (key->IsHoldOrDown(DIK_W) && physics->IsOnGround()) state = State::Jump;
		}
		else if (key->IsHoldOrDown(DIK_A))
		{
			is_mirrored_animation = true;
			if (key->IsHoldOrDown(DIK_LSHIFT) && kirby_state != KirbyState::Full) state = State::Run;
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
		if (key->IsHoldOrDown(DIK_SPACE) && kirby_state != KirbyState::Full)
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
		if (kirby_state == KirbyState::Full) state = State::Idle;

		if (key->IsMouseRButtonHoldOrDown())
		{
			state = State::Action;
		}
		else 
			state = State::Idle;
	}
		break;
	case State::Attack:		//TODO::
	{
		attack_limit_time += context->GetSubSystem<Timer>()->GetDeltaTimeMS();
		if (key->IsMouseLButtonHoldOrDown() && attack_limit_time < 450.0f)
		{
			state = State::Attack;
		}
		else
		{
			attack_limit_time = 0.0f;
			state = State::Idle;
		}
		break;
	}
	case State::Damaged:
	{
		if (animator->IsPaused() == true)
		{
			state = State::Idle;
			animator->Play();
		}
		break;
	}
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
	case State::Pulled:
	{
		if (key->IsMouseRButtonFree()) state = State::Walk;
		break;
	}
	case State::Run:
		break;
	case State::Action:
		break;
	case State::Damaged:
	{
		if (key->IsMouseLButtonFree()) state = State::Walk;
		break;
	}
	case State::Dead:
		actor->SetActive(false);
		break;
	}
}

void StateComponent::UpdateBoss()
{
	auto AiScript = actor->GetComponent<AiScriptBasicComponent>();
	static StopWatch stop_watch;

	switch (state)
	{
	case State::Idle:
	{
		
	}
		break;
	case State::Walk:
	{
		if (AiScript->GetIsRight() == true) is_mirrored_animation = false;
		else is_mirrored_animation = true;
	}
	break;
	case State::Jump:
	{

		break;
	}
	case State::Action:
		break;
	case State::Damaged:
	{
		break;
	}
	case State::Dead:
		actor->SetActive(false);
		break;
	}
}
