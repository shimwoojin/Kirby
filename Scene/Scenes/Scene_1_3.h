#pragma once
#include "Scene.h"

class Scene_1_3 : public Scene
{
public:
	Scene_1_3(class Context* const context);

	virtual void Init() override;

private:
	void AddMapTile();
};

