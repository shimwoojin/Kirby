#include "stdafx.h"
#include "InputManager.h"

InputManager::~InputManager()
{
	if (mouse_device != nullptr)
	{
		mouse_device->Unacquire();
		SAFE_RELEASE(mouse_device);
	}

	if (key_device != nullptr)
	{
		key_device->Unacquire();
		SAFE_RELEASE(key_device);
	}

	SAFE_RELEASE(direct_input_device);
}

bool InputManager::Initialize()
{
	//===========================================
	// [Initialize]
	//===========================================
	ZeroMemory(input_key_state, sizeof(BYTE) * 256);
	ZeroMemory(&input_mouse_state, sizeof(DIMOUSESTATE));

	ZeroMemory(key_state, sizeof(KEY_STATE) * 256);
	ZeroMemory(mouse_state, sizeof(KEY_STATE) * 3);
	ZeroMemory(&mouse_position, sizeof(POINT));

	//===========================================
	// [Create Direct Input Device]
	//===========================================
	HRESULT hr = DirectInput8Create(
		Settings::Get().GetWindowInstance(),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&direct_input_device),
		nullptr
	);
	if (FAILED(hr)) { assert(false); return false; }

	//===========================================
	// [Create Key Device]
	//===========================================
	hr = direct_input_device->CreateDevice(
		GUID_SysKeyboard,
		&key_device,
		nullptr
	);
	if (FAILED(hr)) { assert(false); return false; }

	key_device->SetDataFormat(&c_dfDIKeyboard);

	hr = key_device->SetCooperativeLevel(
		Settings::Get().GetWindowhandle(),
		DISCL_NONEXCLUSIVE |
		DISCL_FOREGROUND
	);
	if (FAILED(hr)) { assert(false); return false; }

	while (key_device->Acquire() == DIERR_INPUTLOST);

	//===========================================
	// [Create Mouse Device]
	//===========================================
	hr = direct_input_device->CreateDevice(
		GUID_SysMouse,
		&mouse_device,
		nullptr
	);
	if (FAILED(hr)) { assert(false); return false; }

	mouse_device->SetDataFormat(&c_dfDIMouse);

	hr = mouse_device->SetCooperativeLevel(
		Settings::Get().GetWindowhandle(),
		DISCL_NONEXCLUSIVE |
		DISCL_FOREGROUND
	);
	if (FAILED(hr)) { assert(false); return false; }

	while (mouse_device->Acquire() == DIERR_INPUTLOST);


	return true;
}

void InputManager::Update()
{
	if (key_device == nullptr || mouse_device == nullptr)
	{
		assert(false);
		return;
	}

	//=======================================================
	// [Read Data]
	//=======================================================
	HRESULT hr = key_device->GetDeviceState(256, input_key_state);
	if (FAILED(hr))
	{
		while (key_device->Acquire() == DIERR_INPUTLOST);
		hr = key_device->GetDeviceState(256, &input_key_state);
		if (FAILED(hr)) return;
	}

	hr = mouse_device->GetDeviceState(sizeof(DIMOUSESTATE), &input_mouse_state);
	if (FAILED(hr))
	{
		while (mouse_device->Acquire() == DIERR_INPUTLOST);
		hr = mouse_device->GetDeviceState(sizeof(DIMOUSESTATE), &input_mouse_state);
		if (FAILED(hr)) return;
	}


	//=======================================================
	// [Update Mouse]
	//=======================================================
	GetCursorPos(&mouse_position);
	ScreenToClient(Settings::Get().GetWindowhandle(), &mouse_position);

	mouse_position.x -= static_cast<LONG>(Settings::Get().GetWidth() / 2);
	mouse_position.y = -mouse_position.y + static_cast<LONG>(Settings::Get().GetHeight() / 2);

	for (int button = 0; button < 3; button++)
	{
		if (input_mouse_state.rgbButtons[button] & 0x80)
		{
			switch (mouse_state[button])
			{
			case KEY_FREE:
			case KEY_UP:
				mouse_state[button] = KEY_DOWN; break;
			case KEY_DOWN:
				mouse_state[button] = KEY_HOLD; break;
			}
		}
		else
		{
			switch (mouse_state[button])
			{
			case KEY_HOLD:
			case KEY_DOWN:
				mouse_state[button] = KEY_UP; break;
			case KEY_UP:
				mouse_state[button] = KEY_FREE; break;
			}
		}
	}

	//=======================================================
	// [Update Keyboard]
	//=======================================================
	for (int key = 0; key < 256; key++)
	{
		if (input_key_state[key] & 0x80)
		{
			switch (key_state[key])
			{
			case KEY_FREE:
			case KEY_UP:
				key_state[key] = KEY_DOWN; break;
			case KEY_DOWN:
				key_state[key] = KEY_HOLD; break;
			}
		}
		else
		{
			switch (key_state[key])
			{
			case KEY_HOLD:
			case KEY_DOWN:
				key_state[key] = KEY_UP; break;
			case KEY_UP:
				key_state[key] = KEY_FREE; break;
			}
		}
	}
}