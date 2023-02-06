#pragma once
//Settings.h

#include "stdafx.h"

class Settings final
{
public:
	static Settings& Get()
	{
		static Settings instance;
		return instance;
	}

	HWND GetWindowhandle() { return handle; }
	void SetWindowhandle(HWND handle) { this->handle = handle; }

	const float& GetWidth() { return width; }
	void SetWidth(const float& width) { this->width = width; }

	const float& GetHeight() { return height; }
	void SetHeight(const float& height) { this->height = height; }

	HINSTANCE GetWindowInstance() { return instance; }
	void SetWindowInstance(HINSTANCE instance) { this->instance = instance; }

private:
	Settings() = default;
	~Settings() = default;

	Settings(const Settings&) = delete;
	Settings& operator=(const Settings&) = delete;

private:
	HWND handle = nullptr;
	HINSTANCE instance = nullptr;

	float width = 0.0f;
	float height = 0.0f;
};