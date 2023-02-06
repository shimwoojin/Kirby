#pragma once

struct ISubSystem
{
	ISubSystem(class Context* context) : context(context) {};
	virtual ~ISubSystem() = default;

	virtual bool Initialize() = 0;
	virtual void Update() = 0;

	const class Context* const GetContext() const { return context; }

protected:
	class Context* context = nullptr;
};