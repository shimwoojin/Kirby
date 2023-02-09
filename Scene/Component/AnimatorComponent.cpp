#include "stdafx.h"
#include "Scene/Scenes/Scene.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Actors/Player.h"
#include "Scene/Actors/Monster.h"
#include "AnimatorComponent.h"
#include "StateComponent.h"
#include "TransformComponent.h"

AnimatorComponent::AnimatorComponent(Context* const context, Actor* const actor, TransformComponent* const transform)
	:IComponent(context, actor, transform)
{
	timer = context->GetSubSystem<Timer>();
	resource_manager = context->GetSubSystem<ResourceManager>();
}

void AnimatorComponent::Initialize()
{
	SetStandardMaterial();
}

void AnimatorComponent::Update()
{
	//렌더링 뭐할지 정해줌. 플레이어(hungry, full, fire, ice, monster 등 여기서 애니메이션을 정함)
	WhatRendering();

	if (current_animation.expired() == true || IsPlaying() == false) return;


	//=======================================================================
	//=======================================================================
	//=======================================================================

	frame_counter += timer->GetDeltaTimeMS();

	if (frame_counter > GetCurrentKeyframe()->time)
	{
		current_frame_number++;

		switch (current_animation.lock()->GetRepeatType())
		{
		case RepeatType::Once:
		{
			if (current_frame_number >= current_animation.lock()->GetKeyframeCount())
			{
				current_frame_number = current_animation.lock()->GetKeyframeCount() - 1;
				Pause();
			}
			break;
		}

		case RepeatType::Loop:
		{
			current_frame_number %= current_animation.lock()->GetKeyframeCount();
			break;
		}

		}

		frame_counter = 0.0;
	}

}

void AnimatorComponent::Destroy()
{
}

const std::shared_ptr<class Animation> AnimatorComponent::GetCurrentAnimation() const
{
	return current_animation.expired() ? nullptr : current_animation.lock();
}

void AnimatorComponent::SetCurrentAnimation(const std::string& animation_name)
{
	if (current_animation.lock().get() == animations[animation_name].get()) return;

	if (animations.find(animation_name) == animations.end())
	{
		assert(false);
		return;
	}

	current_animation = animations[animation_name];
	current_frame_number = 0;
	frame_counter = 0.0f;

}

const Keyframe* const AnimatorComponent::GetCurrentKeyframe() const
{
	if (current_animation.expired() == true)
	{
		assert(false);
		return nullptr;
	}

	return current_animation.lock()->GetKeyframeFromIndex(current_frame_number);
}

void AnimatorComponent::AddAnimation(const std::string& animation_name, const std::shared_ptr<class Animation>& animation)
{
	if (animations.find(animation_name) != animations.end())
	{
		assert(false);
		return;
	}

	animations[animation_name] = animation;
}

void AnimatorComponent::AddAnimation(const std::string& path)
{
	auto resource_manager = context->GetSubSystem<ResourceManager>();
	auto animation = resource_manager->Load<Animation>(path);

	if (animation == nullptr)
	{
		assert(false);
		return;
	}

	AddAnimation(animation->GetResourceName(), animation);
}

void AnimatorComponent::Play()
{
	animation_mode = AnimationMode::Play;
	frame_counter = 0.0f;
}

void AnimatorComponent::Stop()
{
	animation_mode = AnimationMode::Stop;
	current_frame_number = 0;
	frame_counter = 0.0f;
}

void AnimatorComponent::Pause()
{
	animation_mode = AnimationMode::Pause;
}

void AnimatorComponent::SetStandardMaterial()
{
		vertex_shader = resource_manager->Load<Shader>("./Assets/Shader/Animation.hlsl").get()->GetVertexShader();
		pixel_shader = resource_manager->Load<Shader>("./Assets/Shader/Animation.hlsl").get()->GetPixelShader();

		input_layout = std::make_shared<D3D11_InputLayout>(context->GetSubSystem<Graphics>());
		input_layout->Create(D3D11_VertexTexture::descs, D3D11_VertexTexture::count, vertex_shader->GetShaderBlob());
}

void AnimatorComponent::WhatRendering()
{
	auto type = actor->GetActorType();
	auto state = actor->GetComponent<StateComponent>();

	if (type == ActorType::Player)
	{
		auto kirby_state = static_cast<Player*>(actor)->GetKirbyState();

		if (kirby_state == KirbyState::Hungry)
		{
			switch (state->GetState())
			{
			case State::Idle:			 SetCurrentAnimation("Idle");					break;
			case State::Walk:			 SetCurrentAnimation("Walk");				break;
			case State::Jump:			 SetCurrentAnimation("Jump");				break;
			case State::OnAir:			 SetCurrentAnimation("OnAir");				break;
			case State::Run:			 SetCurrentAnimation("Run");					break;
			case State::Fly:				 SetCurrentAnimation("Fly");					break;
			case State::Action:		 SetCurrentAnimation("Action1"); 			break;
			case State::Damaged:	 SetCurrentAnimation("Damaged");		break;
			case State::Dead: 														break;
			}
		}
		else if (kirby_state == KirbyState::Full)
		{
			switch (state->GetState())
			{
			case State::Idle:		 SetCurrentAnimation("Full_Idle");				break;
			case State::Walk:		 SetCurrentAnimation("Full_Walk");				break;
			case State::Jump:		 SetCurrentAnimation("Full_Jump");			break;
			case State::OnAir:		 SetCurrentAnimation("Full_OnAir");			break;
			case State::Run: break;
			case State::Fly: break;
			case State::Action: break;
			case State::Damaged: break;
			case State::Dead: 														break;
			}
		}
		else if (kirby_state == KirbyState::Fire)
		{
			switch (state->GetState())
			{
			case State::Idle:			 SetCurrentAnimation("Fire_Idle");				break;
			case State::Walk:			 SetCurrentAnimation("Fire_Walk");			break;
			case State::Jump:			 SetCurrentAnimation("Fire_Jump");			break;
			case State::OnAir:			 SetCurrentAnimation("Fire_OnAir");			break;
			case State::Run:			 SetCurrentAnimation("Fire_Run");				break;
			case State::Fly:				 SetCurrentAnimation("Fire_Fly");				break;
			case State::Attack:		 SetCurrentAnimation("Fire_Attack");			break;
			case State::Action: break;
			case State::Damaged:	 SetCurrentAnimation("Fire_Damaged");		break;
			//case State::Attack: SetCurrentAnimation("");		break;
			case State::Dead: 														break;
			}
		}
	}
	else if (type == ActorType::Monster)
	{
		auto m_type = static_cast<Monster*>(actor)->GetAttribute();

		if (m_type == Monster_Attribute::Fire)
		{
			switch (state->GetState())
			{
			case State::Idle: break;
			case State::Walk: SetCurrentAnimation("M_Fire1_Walk");	break;
			case State::Pulled: SetCurrentAnimation("M_Fire1_Pulled");	break;
			case State::Jump: break;
			case State::OnAir: break;
			case State::Run: break;
			case State::Fly: break;
			case State::Action: break;
			case State::Damaged: SetCurrentAnimation("M_Fire1_Damaged"); break;
			case State::Dead: break;
			}
		}
		else if (m_type == Monster_Attribute::Ice)
		{
			switch (state->GetState())
			{
			case State::Idle: break;
			case State::Walk: SetCurrentAnimation("M_Ice1_Walk");		break;
			case State::Pulled: SetCurrentAnimation("M_Ice1_Pulled"); 	break;
			case State::Jump: break;
			case State::OnAir: break;
			case State::Run: break;
			case State::Fly: break;
			case State::Action: break;
			case State::Damaged: SetCurrentAnimation("M_Ice1_Damaged"); break;
			case State::Dead: break;
			}

		}
		else if(m_type == Monster_Attribute::None)
		{
			switch (state->GetState())
			{
			case State::Idle: break;
			case State::Walk: SetCurrentAnimation("M1_Walk");	break;
			case State::Pulled: SetCurrentAnimation("M1_Pulled");	break;
			case State::Jump: break;
			case State::OnAir: break;
			case State::Run: break;
			case State::Fly: break;
			case State::Action: break;
			case State::Damaged: SetCurrentAnimation("M1_Damaged"); break;
			case State::Dead: break;
			}

		}
	}
	else if (type == ActorType::Weapon)
	{
		auto kirby = actor->GetTransform()->GetParent().lock()->GetActor();
		auto kirby_state = static_cast<Player*>(kirby)->GetKirbyState();
		
		if (kirby_state == KirbyState::Hungry)
			SetCurrentAnimation("Weapon_Swallow");
		else if (kirby_state == KirbyState::Fire)
			SetCurrentAnimation("Weapon_Fire");
	}
}
