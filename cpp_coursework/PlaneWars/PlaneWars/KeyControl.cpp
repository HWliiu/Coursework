#include "stdafx.h"
#include "KeyControl.h"


KeyControl::KeyControl()
{
	for (int i = 0; i < 256; i++) {
		keyPressState[i] = false;
	}
}


KeyControl::~KeyControl()
{
}

void KeyControl::UpdateKey(HWND hWnd, UINT message, WPARAM wParam, bool pressDown) {
	keyPressState[wParam] = pressDown;
}
bool KeyControl::IsKeyDown(WPARAM keyCode) {
	return keyPressState[keyCode];
}
