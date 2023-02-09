#include "stdafx.h"
#include "ActionComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "../Actors/Actor.h"
#include "../Actors/Player.h"
#include "../Actors/Monster.h"

void ActionComponent::Initialize()
{
}

void ActionComponent::Update()
{
    auto weapon = scene->GetWeapon();
    weapon->SetActive(false);

    if (is_update == false) return;

    weapon->SetActive(true);

    auto state = actor->GetComponent<StateComponent>();
    if (state->GetState() == State::Action)
    {
        Swallow();
    }
    else if (state->GetState() == State::Attack)
    {
        Attack();
    }

}

void ActionComponent::Destroy()
{
}

void ActionComponent::Swallow()
{
    auto weapon = scene->GetWeapon();

    auto scale = actor->GetTransform()->GetScale();
    float width = 3.0f;
    float height = 1.2f;
    bool IsLeft = actor->GetComponent<StateComponent>()->GetIsMirroredAnimation();

    if (IsLeft == true) weapon->GetTransform()->SetLocalPosition(D3DXVECTOR3(-width / 2, 0.0f, 1.0f));
    else weapon->GetTransform()->SetLocalPosition(D3DXVECTOR3(width / 2, 0.0f, 1.0f));

    weapon->GetTransform()->SetScale(D3DXVECTOR3(scale.x * width, scale.y * height, 1.0f));

    auto actors = scene->GetActors();
    for (auto& scene_actor : actors)
    {
        auto type = scene_actor->GetActorType();
        if (type == ActorType::Monster)
        {
            if (Collide::IsCollidedActionBox(actor, scene_actor.get(), width, height) == true)
            {
                auto position = actor->GetTransform()->GetPosition();
                auto monster_position = scene_actor->GetTransform()->GetPosition();

                D3DXVECTOR3 inhale_vector = position - monster_position;

                D3DXVec3Normalize(&inhale_vector, &inhale_vector);

                monster_position += inhale_vector;

                scene_actor->GetTransform()->SetPosition(monster_position);     //몬스터 끌어오기 처리
                scene_actor->GetComponent<StateComponent>()->SetState(State::Pulled);   //몬스터 상태 pulled로 변경

                if (Collide::IsCollided(actor, scene_actor.get()) == true)  //끌어오다가 player와 몬스터가 닿으면
                {
                    scene_actor->SetActive(false);
                    auto attribute = std::static_pointer_cast<Monster>(scene_actor)->GetAttribute();
                    static_cast<Player*>(actor)->SetKirbyState(KirbyState::Full);
                    static_cast<Player*>(actor)->SetKirbyEaten(attribute);
                }
            }
        }
    }
}

void ActionComponent::Attack()
{
    auto weapon = scene->GetWeapon();

    auto scale = actor->GetTransform()->GetScale();
    float width = 1.5f;
    float height = 1.0f;
    bool IsLeft = actor->GetComponent<StateComponent>()->GetIsMirroredAnimation();

    if (IsLeft == true) weapon->GetTransform()->SetLocalPosition(D3DXVECTOR3(-(width / 2 + 0.5f), 0.0f, 1.0f));
    else weapon->GetTransform()->SetLocalPosition(D3DXVECTOR3(width / 2 + 0.5f, 0.0f, 1.0f));

    weapon->GetTransform()->SetScale(D3DXVECTOR3(scale.x * width, scale.y * height, 1.0f));

    auto actors = scene->GetActors();
    for (auto& scene_actor : actors)
    {
        auto type = scene_actor->GetActorType();
        if (type == ActorType::Monster)
        {
            if (Collide::IsCollidedActionBox(actor, scene_actor.get(), width, height) == true)
            {
                if (scene_actor->GetComponent<StateComponent>()->GetState() != State::Damaged)
                {
                    scene_actor->GetComponent<StateComponent>()->SetState(State::Damaged);   //몬스터 상태 pulled로 변경
                }
                std::static_pointer_cast<Monster>(scene_actor)->SubHp();
                if(std::static_pointer_cast<Monster>(scene_actor)->GetHp() <= 0.0f)
                    scene_actor->GetComponent<StateComponent>()->SetState(State::Dead);
            }
        }
    }
}
