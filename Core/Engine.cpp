#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	context = new Context();

	context->RegisterSubSystem<Timer>();
	context->RegisterSubSystem<InputManager>();
	context->RegisterSubSystem<ResourceManager>();
	context->RegisterSubSystem<Graphics>();
	context->RegisterSubSystem<SceneManager>();
	context->RegisterSubSystem<Renderer>();

	context->InitializeSubsystems();
}

Engine::~Engine()
{
	SAFE_DELETE(context);
}

void Engine::Update()
{
	context->UpdateSubSystems();
}

void Engine::Render()
{
	//Renderer* renderer = context->GetSubSystem<Renderer>();
	//renderer->Update();
}
