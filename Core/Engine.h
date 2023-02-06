#pragma once

class Engine final
{
public:
	Engine();
	~Engine();

	void Update();
	void Render();

	Context* GetContext() { return context; }

private:
	class Context* context = nullptr;
};

