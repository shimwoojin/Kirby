#include "stdafx.h"
#include "AiScriptBossComponent.h"
#include "Scene/Actors/Actor.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "AnimatorComponent.h"

void AiScriptBossComponent::Initialize()
{
	stop_watch.Start();
	jump_timer.Start();
}

void AiScriptBossComponent::Update()
{
	auto position = transform->GetPosition();
	auto state = actor->GetComponent<StateComponent>();
	auto animator = actor->GetComponent<AnimatorComponent>();

	if (stop_watch.GetElapsedTimeMs() > 4000.0f)
	{
		random = Math::Random(0, 7);
		stop_watch.Start();

		if (random == 0) state->SetState(State::Idle);
		else if (random >= 1 && random <= 3) state->SetState(State::Walk);
		else if (random >= 4 && random <= 5)
		{
			state->SetState(State::Jump);
			jump_timer.Start();
		}
		else if (random >= 6 && random <= 7) state->SetState(State::Action);
	}

	switch (state->GetState())
	{
	case State::Idle:
	{
		break;	//아무 동작 안함
	}
	case State::Walk:
	{
		break;	//aiscriptbasic에서 처리
	}
	case State::Jump:
	{
		if (jump_timer.GetElapsedTimeMs() > 800.0f)
		{
			position.x = Math::Random(50.0f, 950.0f);
			position.y = 700.0f;
			jump_timer.Start();
		}
		break;
	}
	case State::Action:
	{
		break;
	}
	case State::Damaged:
	{
		if (damage_timer.GetElapsedTimeMs() > 300.0f) state->SetState(State::Jump);
		break;
	}
	}

	actor->GetTransform()->SetPosition(position);
}

void AiScriptBossComponent::Destroy()
{
}
