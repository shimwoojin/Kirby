#include "stdafx.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Scene/Actors/Actor.h"

void PhysicsComponent::Initialize()
{
}

void PhysicsComponent::Update()
{
	if (is_update == false) return;

	is_on_ground = false;
	auto position = transform->GetPosition();

	if (scene != nullptr)
	{
		std::vector<std::shared_ptr<Actor>> actors = scene->GetActors();

		for (const auto& scene_actor : actors)
		{
			ActorType type = scene_actor->GetActorType();
			if (type == ActorType::MapTile)
			{
				if (CheckOnGround(scene_actor.get()))
				{
					is_on_ground = true;
					gravity = 0.0f;
				}
			}
		}
	}

	if (is_on_ground == false)
	{
		gravity += 0.05f;
		if (gravity > 4.0f) gravity = 4.0f;

		position.y -= gravity;
		transform->SetPosition(position);
	}
}

void PhysicsComponent::Destroy()
{
}

bool PhysicsComponent::CheckOnGround(class Actor* map_tile)
{
	D3DXVECTOR3 tile_scale = map_tile->GetTransform()->GetScale();
	D3DXVECTOR3 tile_position = map_tile->GetTransform()->GetPosition();

	D3DXVECTOR3 actor_scale = actor->GetTransform()->GetScale();
	D3DXVECTOR3 actor_position = actor->GetTransform()->GetPosition();

	int min_x1 = actor_position.x - actor_scale.x / 2;
	int max_x1 = actor_position.x + actor_scale.x / 2;
	int min_y1 = actor_position.y - actor_scale.y / 2;
	int max_y1 = actor_position.y + actor_scale.y / 2;

	int min_x2 = tile_position.x - tile_scale.x / 2;
	int max_x2 = tile_position.x + tile_scale.x / 2;
	int min_y2 = tile_position.y - tile_scale.y / 2;
	int max_y2 = tile_position.y + tile_scale.y / 2;

	if (min_x1 < max_x2 && max_x1 > min_x2 && min_y1 < max_y2 && max_y1 > max_y2) return true;
	else return false;
}

