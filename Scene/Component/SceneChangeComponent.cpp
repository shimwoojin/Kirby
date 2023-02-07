#include "stdafx.h"
#include "SceneChangeComponent.h"
#include "../Actors/Actor.h"

std::string SceneChangeComponent::scene_names[10] =
{
	"1-1", "1-2", "1-3", "1-4", "1-5",
	"2-1", "2-2", "2-3", "2-4", "2-5"
};
uint SceneChangeComponent::scene_count = 1;

void SceneChangeComponent::Initialize()
{
	key = context->GetSubSystem<InputManager>();
	scene_manager = context->GetSubSystem<SceneManager>();
}

void SceneChangeComponent::Update()
{
	if (key->IsHoldOrDown(DIK_W))
	{
		auto actors = scene->GetActors();
		for (const auto& scene_actor : actors)
		{
			auto type = scene_actor.get()->GetActorType();
			if (type == ActorType::Player)
			{
				if (Collide::IsCollided(scene_actor.get(), actor) == true)
				{
					scene_manager->SetCurrentScene(scene_names[scene_count++]);
				}
			}
		}
	}
}

void SceneChangeComponent::Destroy()
{
}

void SceneChangeComponent::SetScene(Scene* scene)
{
	this->scene = scene;
}
