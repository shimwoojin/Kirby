#pragma once

struct SceneSize
{
	uint min_x;
	uint max_x;
	uint min_y;
	uint max_y;
};

class Scene
{
public:
	Scene(class Context* const context);
	virtual ~Scene();
	
	virtual void Init() = 0;
	void Update();

	const std::shared_ptr<class Actor> CreateActor(const bool& is_active = true);
	void AddActor(const std::shared_ptr<class Actor>& actor);

	const std::vector<std::shared_ptr<class Actor>>& GetActors() const { return actors; }

	void SetUpdate(bool update) { is_update = update; }
	void SetSceneChange(bool change) { scene_change = change; }

	const SceneSize& GetSceneSize() const { return scene_size; }
	const std::shared_ptr<class Actor>& GetPlayer() { return player; }

protected:
	std::shared_ptr<class Actor> AddBackGround(std::string path);
	std::shared_ptr<class Actor> AddDoor(std::string path, uint x, uint y);

protected:
	static std::shared_ptr<class Actor> player;
	class Context* context = nullptr;
	SceneSize scene_size;

private:
	class Renderer* renderer = nullptr;

	bool is_update = true;
	bool scene_change = false;

	std::vector<std::shared_ptr<class Actor>> actors;

};