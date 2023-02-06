//Program.cpp

#include"stdafx.h"
#include"Core/Window.h"
#include"Core/Engine.h"

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	// ������ ����
	Window::Create(hInstance, 1024, 768);
	Window::Show();

	Settings::Get().SetWindowhandle(Window::global_handle);
	Settings::Get().SetWindowInstance(Window::global_instance);
	Settings::Get().SetWidth(static_cast<float>(Window::GetWidth()));
	Settings::Get().SetHeight(static_cast<float>(Window::GetHeight()));

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	//������Ʈ
	while (Window::Update())
	{
		engine->Update();
		engine->Render();
	}

	Window::Destroy();
}