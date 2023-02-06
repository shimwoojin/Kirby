#pragma once
#include "IComponent.h"
class AiScriptBasicComponent : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void SetMinMaxX(uint min, uint max);

	bool GetIsRight() { return move_right; }

private:
	bool move_right = true;

	uint min_x = 100;
	uint max_x = 200;
};

