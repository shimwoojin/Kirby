#include "stdafx.h"
#include "../Scenes/Scene.h"
#include "../Actors/Actor.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"

void ColliderComponent::Initialize()
{
    stop_watch.Start();
}

void ColliderComponent::Update()
{
    collide_maptile = CollideMapTile();
    is_update = true;

    collide_time = stop_watch.GetElapsedTimeMs();

    if (collide_time < 1000.0f) is_update = false;      //충돌 후 바로 재충돌 방지 -> 1초

    if (is_update == false) return;

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
            if (collide_check != Collide_Null && scene_actor->IsActive() == true)
            {
                stop_watch.Start();

                actor->GetComponent<StateComponent>()->SetState(State::Damaged);
                collide_monster_dir = collide_check;
                return true;
            }
        }
    }

    return false;
}
