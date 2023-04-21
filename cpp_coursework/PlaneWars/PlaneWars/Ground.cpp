#include "stdafx.h"
#include "Ground.h"


Ground::Ground()
{
}


Ground::~Ground()
{
}

void Ground::Paint(HDC hdc) {
	MoveToEx(hdc, 0, 680, nullptr);
	LineTo(hdc, 1920, 680);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	for (int i = 0; i < 1920; i += 40) {
		MoveToEx(hdc, i, 681, nullptr);
		LineTo(hdc, i-30, 695);
	}
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}
