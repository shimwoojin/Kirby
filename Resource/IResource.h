#pragma once

enum class ResourceType : uint
{
	Unknown,
	Animation,
	Texture2D,
	Shader,
	Mesh,
	Material
};

class IResource
{
public:
	template <typename T>
	static constexpr ResourceType DeduceResourceType();

public:
	IResource(class Context* const context, const ResourceType type = ResourceType::Unknown);
	virtual ~IResource() = default;

	virtual bool SaveToFile(const std::string& path) = 0;
	virtual bool LoadFromFile(const std::string& path) = 0;

	ResourceType GetResourceType() const { return resource_type; }
	std::string GetResourceName() const { return resource_name; }
	std::string GetResourcePath() const { return resource_path; }

	void SetResourceName(const std::string& name) { this->resource_name = name; }
	void SetResourcePath(const std::string& path) { this->resource_path = path; }

protected:
	class Context* context = nullptr;
	ResourceType resource_type = ResourceType::Unknown;
	std::string resource_name = "";
	std::string resource_path = "";
};


