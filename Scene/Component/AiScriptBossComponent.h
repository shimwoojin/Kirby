#pragma once
#include "IComponent.h"
class AiScriptBossComponent : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void SetDamageTimer() { damage_timer.Start(); }

private:
	StopWatch stop_watch;
	StopWatch jump_timer;
	StopWatch damage_timer;

	int random = 0;
};

