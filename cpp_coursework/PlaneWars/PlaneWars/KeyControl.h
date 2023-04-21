#pragma once
class KeyControl
{
private:
	bool keyPressState[256];
public:
	KeyControl();
	~KeyControl();
	void UpdateKey(HWND hWnd, UINT message, WPARAM wParam, bool pressDown = true);
	bool IsKeyDown(WPARAM keyCode);
};

