#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(Context* context)
	: ISubSystem(context)
{
	std::string root_directory = GetAssetDirectory();

	RegisterDirectory(AssetType::Animation, root_directory + "Animation/");
	RegisterDirectory(AssetType::Shader, root_directory + "Shader/");
	RegisterDirectory(AssetType::Texture, root_directory + "Texture/");
}

bool ResourceManager::Initialize()
{
	return true;
}

void ResourceManager::Update()
{
}

bool ResourceManager::HasResource(const std::string& resource_name, const ResourceType& resource_type)
{
	for (const auto& resource : resource_groups[resource_type])
	{
		if (resource->GetResourceName() == resource_name)
			return true;
	}

	return false;
}

const std::string ResourceManager::GetAssetDirectory(const AssetType& type)
{
	return asset_directories[type];
}

void ResourceManager::RegisterDirectory(const AssetType& type, const std::string& directory)
{
	asset_directories[type] = directory;
}