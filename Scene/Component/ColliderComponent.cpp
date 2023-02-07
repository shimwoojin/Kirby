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
    collide_maptile = CollideMapTile();
    collide_monster = CollideMonster();
}

void ColliderComponent::Destroy()
{
}

bool ColliderComponent::CollideMapTile()
{
    collide_tile_dir = Collide_Null;

    auto actors = scene->GetActors();
    for (auto& scene_actor : actors)
    {
        auto type = scene_actor->GetActorType();
        if (type == ActorType::MapTile)
        {
            uint collide_check = Collide::GetCollide_Dir(actor, scene_actor.get());
            if (collide_check != Collide_Null)
            {
                collide_tile_dir = collide_check;
                return true;
            }
        }
    }

    return false;
}

bool ColliderComponent::CollideMonster()
{
    collide_monster_dir = Collide_Null;

    auto actors = scene->GetActors();
    for (auto& scene_actor : actors)
    {
        auto type = scene_actor->GetActorType();
        if (type == ActorType::Monster)
        {
            uint collide_check = Collide::GetCollide_Dir(actor, scene_actor.get());
            if (collide_check != Collide_Null)
            {
                collide_monster_dir = collide_check;
                return true;
            }
        }
    }

    return false;
}
