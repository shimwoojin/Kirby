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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(Settings::Get().GetWindowhandle());
	auto graphics = context->GetSubSystem<Graphics>();
	ImGui_ImplDX11_Init(graphics->GetDevice(), graphics->GetDeviceContext());
}

Engine::~Engine()
{
	SAFE_DELETE(context);
}

void Engine::Update()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	context->UpdateSubSystems();
}

void Engine::Render()
{
	Renderer* renderer = context->GetSubSystem<Renderer>();
	renderer->Update();
}
