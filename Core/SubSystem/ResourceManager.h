#pragma once
#include "ISubSystem.h"
#include "Resource/IResource.h"
#include <filesystem>	//c++17

enum class AssetType : uint
{
	Texture,
	Shader,
	Animation
};

class ResourceManager final : public ISubSystem
{
public:
	ResourceManager(class Context* context);
	~ResourceManager() = default;

	virtual bool Initialize() override;
	virtual void Update() override;

	//=================================
	// [Resource]
	//=================================
	template <typename T>
	const std::shared_ptr<T> Load(const std::string& path);

	template <typename T>
	const std::shared_ptr<T> GetResourceFromName(const std::string& name);

	template <typename T>
	const std::shared_ptr<T> GetResourceFromPath(const std::string& path);

	template <typename T>
	void RegisterResource(const std::shared_ptr<T>& resource);

	bool HasResource(const std::string& resource_name, const ResourceType& resource_type);

	//=================================
	// [Directory]
	//=================================
	const std::string GetAssetDirectory() const { return "Assets/"; }

	const std::string GetAssetDirectory(const AssetType& type);

private:
	void RegisterDirectory(const AssetType& type, const std::string& directory);

private:
	using resource_group_t = std::vector<std::shared_ptr<IResource>>;
	std::map<ResourceType, resource_group_t> resource_groups;

	std::mutex resource_mutex;
	std::map<AssetType, std::string> asset_directories;
};

template<typename T>
inline const std::shared_ptr<T> ResourceManager::Load(const std::string& path)
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");

	if (std::filesystem::exists(path) == false)
	{
		assert(false);
		return nullptr;
	}


	auto last_index = path.find_last_of("\\/");
	auto file_name = path.substr(last_index + 1, path.length());

	last_index = file_name.find_last_of('.');
	auto resource_name = file_name.substr(0, last_index);

	if (HasResource(resource_name, IResource::DeduceResourceType<T>()))
		return GetResourceFromName<T>(resource_name);

	std::shared_ptr<T> resource = std::make_shared<T>(context);
	resource->SetResourceName(resource_name);
	resource->SetResourcePath(path);

	if (resource->LoadFromFile(path) == false)
	{
		assert(false);
		return nullptr;
	}

	RegisterResource<T>(resource);

	return resource;
}

template<typename T>
inline const std::shared_ptr<T> ResourceManager::GetResourceFromName(const std::string& name)
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");

	for (const auto& resource : resource_groups[IResource::DeduceResourceType<T>()])
	{
		if (resource->GetResourceName() == name)
			return std::static_pointer_cast<T>(resource);
	}

	return nullptr;
}

template<typename T>
inline const std::shared_ptr<T> ResourceManager::GetResourceFromPath(const std::string& path)
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");

	for (const auto& resource : resource_groups[IResource::DeduceResourceType<T>()])
	{
		if (resource->GetResourcePath() == path)
			return std::static_pointer_cast<T>(resource);
	}

	return nullptr;
}

template<typename T>
inline void ResourceManager::RegisterResource(const std::shared_ptr<T>& resource)
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");

	if (resource == nullptr)
	{
		assert(false);
		return;
	}

	resource_mutex.lock();

	resource_groups[resource->GetResourceType()].emplace_back(resource);

	resource_mutex.unlock();
}