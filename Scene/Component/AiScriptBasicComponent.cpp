#include "stdafx.h"
#include "AiScriptBasicComponent.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/StateComponent.h"

void AiScriptBasicComponent::Initialize()
{
}

void AiScriptBasicComponent::Update()
{
	auto position = transform->GetPosition();
	auto state = actor->GetComponent<StateComponent>();

	switch (state->GetState())
	{
	case State::Idle: break;
	case State::Walk:
	{
		if (position.x >= max_x) move_right = false;
		else if (position.x <= min_x) move_right = true;

		if (move_right == true) position.x += 1;
		else position.x -= 1;

		break;
	}
	case State::Damaged: break;
	case State::Action: break;
	case State::Dead: break;
	}

	transform->SetPosition(position);
}

void AiScriptBasicComponent::Destroy()
{
}

void AiScriptBasicComponent::SetMinMaxX(uint min, uint max)
{
	min_x = min;
	max_x = max;
}
