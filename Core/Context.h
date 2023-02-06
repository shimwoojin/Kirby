#pragma once
#include "stdafx.h"
#include "Core/SubSystem/ISubSystem.h"

class Context final
{
public:
	Context() = default;

	~Context()
	{
		for (auto iter = subsystems.rbegin(); iter != subsystems.rend(); iter++)
			SAFE_DELETE(*iter);
	}

	const bool InitializeSubsystems()
	{
		bool result = true;

		for (const auto& subsystem : subsystems)
		{
			if (subsystem->Initialize() == false)
				result = false;
		}

		return result;
	}

	template<typename T>
	const T* const RegisterSubSystem()
	{
		static_assert(std::is_base_of<ISubSystem, T >::value == true, "Procided type does not implement ISubSystem");

		subsystems.emplace_back(new T(this));

		return static_cast<T*>(subsystems.back());
	}

	template<typename T>
	T* const GetSubSystem()
	{
		static_assert(std::is_base_of<ISubSystem, T > ::value == true, "Procided type does not implement ISubSystem");

		for (const auto& subsystem : subsystems)
		{
			if (typeid(T) == typeid(*subsystem))
				return static_cast<T*>(subsystem);
		}

		return nullptr;
	}

	void UpdateSubSystems()
	{
		for (const auto& subsystem : subsystems)
			subsystem->Update();
	}

private:
	std::vector<ISubSystem*> subsystems;
};