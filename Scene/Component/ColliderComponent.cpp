#include "stdafx.h"
#include "../Scenes/Scene.h"
#include "../Actors/Actor.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

void ColliderComponent::Initialize()
{
}

void ColliderComponent::Update()
{
    collide_maptile = false;
    collide_monster = false;
    collide_maptile = CollideMapTile();
    collide_monster = CollideMonster();
}

void ColliderComponent::Destroy()
{
}

bool ColliderComponent::CollideMapTile()
{
    auto actors = scene->GetActors();
    for (auto& scene_actor : actors)
    {
        auto type = scene_actor->GetActorType();
        if (type == ActorType::MapTile)
        {
            if (Collide::CollideLeftRightDown(actor, scene_actor.get()) == true)
            {
                return true;
            }
        }
    }

    return false;
}

bool ColliderComponent::CollideMonster()
{
    auto actors = scene->GetActors();
    for (auto& scene_actor : actors)
    {
        auto type = scene_actor->GetActorType();
        if (type == ActorType::Monster)
        {
            if (Collide::IsCollided(actor, scene_actor.get()) == true)
            {
                return true;
            }
        }
    }

    return false;
}
