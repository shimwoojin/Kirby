#pragma once
#include "../Component/IComponent.h"

enum class ActorType
{
	None,
	Door,
	Player,
	Monster,
	BackGround,
	MapTile
};

class Actor
{
public:
	Actor(class Context* const context);
	virtual ~Actor();

	void Initialize();
	void Update();
	void Destroy();

	//==========================================
	// [Property]
	//==========================================

	const std::string& GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }
	
	bool IsActive() const { return is_active; }
	void SetActive(const bool& is_active) { this->is_active = is_active; }

	const std::shared_ptr<class TransformComponent>& GetTransform() const { return transform; }
	class TransformComponent* GetTransform_Raw() const { return transform.get(); }

	//==========================================
	// [Component]
	//==========================================

	template<typename T>
	const std::shared_ptr<T> AddComponent();

	template<typename T>
	T* GetComponent_Raw();

	template<typename T>
	const std::shared_ptr<T> GetComponent();

	template<typename T>
	const std::vector<std::shared_ptr<T>> GetComponents();

	const std::vector<std::shared_ptr<IComponent>>& GetAllComponents() const { return components; }

	bool HasComponent(const ComponentType& type);

	template<typename T>
	bool HasComponent();

	template<typename T>
	void RemoveComponent();

	const ActorType& GetActorType() const { return type; }
	void SetActorType(const ActorType& type) { this->type = type; }

private:
	class Context* context = nullptr;
	std::string name;
	std::vector<std::shared_ptr<IComponent>> components;
	ActorType type = ActorType::None;

	bool is_active = true;

	std::shared_ptr<class TransformComponent> transform;
};

template<typename T>
inline const std::shared_ptr<T> Actor::AddComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value == true, "Provider type does not implement IComponent");

	ComponentType type = IComponent::DeduceComponentType<T>();

	if (HasComponent(type) == true)
		return GetComponent<T>();

	components.emplace_back
	(
		std::make_shared<T>
		(
			context,
			this,
			transform.get()
		)
	);
	std::shared_ptr<T> new_component = std::static_pointer_cast<T>(components.back());

	new_component->Initialize();
	new_component->SetComponentType(type);

	if constexpr (std::is_same<T, class TransformComponent>::value == true)
		transform = new_component;

	return new_component;
}

template<typename T>
inline T* Actor::GetComponent_Raw()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provider type does not implement IComponent");

	ComponentType type = IComponent::DeduceComponentType<T>();
	for (const auto& component : components)
	{
		if (component->GetComponentType() == type)
			return std::static_pointer_cast<T>(component).get();
	}

	return nullptr;
}

template<typename T>
inline const std::shared_ptr<T> Actor::GetComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provider type does not implement IComponent");

	ComponentType type = IComponent::DeduceComponentType<T>();
	for (const auto& component : components)
	{
		if (component->GetComponentType() == type)
			return std::static_pointer_cast<T>(component);
	}

	return nullptr;
}

template<typename T>
inline const std::vector<std::shared_ptr<T>> Actor::GetComponents()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provider type does not implement IComponent");

	ComponentType type = IComponent::DeduceComponentType<T>();

	std::vector<std::shared_ptr<T>> temp_components;
	for (const auto& component : components)
		if (component->GetComponentType() == type)
			temp_components.emplace_back(std::static_pointer_cast<T>(component));

	return temp_components;
}

template<typename T>
inline bool Actor::HasComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provider type does not implement IComponent");

	return HasComponent(IComponent::DeduceComponentType<T>());
}

template<typename T>
inline void Actor::RemoveComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provider type does not implement IComponent");

	ComponentType type = IComponent::DeduceComponentType<T>();

	for (auto iter = components.begin(); iter != components.end(); )
	{
		std::shared_ptr<T> component = *iter;

		if (component->GetComponentType() == type)
		{
			component->Destroy();
			//component.reset();

			iter = components.erase(iter);
		}
		else
			iter++;
	}
}
