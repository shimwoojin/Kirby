#include "stdafx.h"
#include "Actor.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshRendererComponent.h"

Actor::Actor(class Context* const context)
	: context(context)
{
	AddComponent<TransformComponent>();
}

Actor::~Actor()
{
}

void Actor::Initialize()
{
	for (const auto& component : components)
		component->Initialize();
}

void Actor::Update()
{
	if (is_active == false) return;

	for (const auto& component : components)
		if(component->IsEnabled() == true)
			component->Update();
}

void Actor::Destroy()
{
	for (const auto& component : components)
		component->Destroy();
}

bool Actor::HasComponent(const ComponentType& type)
{
	for (const auto& component : components)
		if (component->GetComponentType() == type) return true;

	return false;
}
