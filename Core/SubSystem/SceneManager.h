#pragma once
#include "ISubSystem.h"

class SceneManager final : public ISubSystem
{
public:
	using ISubSystem::ISubSystem;
	~SceneManager();

	virtual bool Initialize() override;
	virtual void Update() override;

	const std::map<std::string, std::shared_ptr<class Scene>>& GetAllScenes() const { return scenes; }

	class Scene* const GetCurrentScene();
	std::weak_ptr<Scene> GetCurrentScene_w();
	void SetCurrentScene(const std::string& scene_name);

	template<typename T>
	class Scene* const RegisterScene(const std::string& scene_name);

private:
	std::map<std::string, std::shared_ptr<class Scene>> scenes;
	std::weak_ptr<Scene> current_scene;
};

