#include "stdafx.h"
#include "SceneManager.h"
#include "Scene/Scenes/Scene.h"
#include "Scene/Component/SceneChangeComponent.h"
#include "Scene/Scenes/Scene_1_1.h"
#include "Scene/Scenes/Scene_1_2.h"
#include "Scene/Scenes/Scene_1_3.h"
#include "Scene/Scenes/Scene_1_4.h"
#include "Scene/Scenes/Scene_1_5.h"

SceneManager::~SceneManager()
{
}

bool SceneManager::Initialize()
{
    RegisterScene<Scene_1_1>("1-1");
    RegisterScene<Scene_1_2>("1-2");
    RegisterScene <Scene_1_3>("1-3");
    RegisterScene <Scene_1_4>("1-4");
    RegisterScene <Scene_1_5>("1-5");
    SetCurrentScene("1-1");

    return true;
}

void SceneManager::Update()
{
    if (GetAsyncKeyState(VK_F1) & 0x8000)
    {
        scenes["1-1"]->SetSceneChange(true);
        SceneChangeComponent::scene_count = 0;
        SetCurrentScene("1-1");
    }
    else if (GetAsyncKeyState(VK_F2) & 0x8000)
    {
        scenes["1-2"]->SetSceneChange(true);
        SceneChangeComponent::scene_count = 1;
        SetCurrentScene("1-2");
    }
    else if (GetAsyncKeyState(VK_F3) & 0x8000)
    {
        scenes["1-3"]->SetSceneChange(true);
        SceneChangeComponent::scene_count = 2;
        SetCurrentScene("1-3");
    }
    else if (GetAsyncKeyState(VK_F4) & 0x8000)
    {
        scenes["1-4"]->SetSceneChange(true);
        SceneChangeComponent::scene_count = 3;
        SetCurrentScene("1-4");
    }
    else if (GetAsyncKeyState(VK_F5) & 0x8000)
    {
        scenes["1-5"]->SetSceneChange(true);
        SceneChangeComponent::scene_count = 4;
        SetCurrentScene("1-5");
    }

    if (current_scene.expired()) assert(false);

    if (current_scene.expired() != true)
        current_scene.lock()->Update();
}

Scene* const SceneManager::GetCurrentScene()
{
    return current_scene.expired() ? nullptr : current_scene.lock().get();
}

std::weak_ptr<Scene> SceneManager::GetCurrentScene_w()
{
    return current_scene.expired() ? std::weak_ptr<Scene>() : current_scene;
}

void SceneManager::SetCurrentScene(const std::string& scene_name)
{
    if (scenes.find(scene_name) == scenes.end())
    {
        assert(false);
        return;
    }

    current_scene = scenes[scene_name];
    current_scene.lock()->SetSceneChange(true);
}

template<typename T>
Scene* const SceneManager::RegisterScene(const std::string& scene_name)
{
    if (scenes.find(scene_name) != scenes.end())
    {
        assert(false);
        return nullptr;
    }

    //static_assert(std::is_base_of<Scene, T>::value, "This type is not based of Scene");
    std::shared_ptr<Scene> new_scene = std::make_shared<T>(context);
    new_scene->Init();

    scenes[scene_name] = new_scene;

    return scenes[scene_name].get();
}
