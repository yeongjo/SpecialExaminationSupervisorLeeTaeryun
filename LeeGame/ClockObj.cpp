#include "ClockObj.h"
#include <atlimage.h>

CImage *ClockObj::clockImg = nullptr;

ClockObj::ClockObj(int x, int y) : Obj(1) {
	p.set(x, y);
	size.set(29*2, 31*2);
	loadImg();
	time = (GameM::getIns().getTime()-1) * 90.f;
}


ClockObj::~ClockObj() {
}

inline void ClockObj::loadImg() {
	if (clockImg) return;
	clockImg = new CImage();
	auto _t = SUCCEEDED(clockImg->Load(L"img/clock.png"));
	assert(_t);
	
}

inline void ClockObj::tick() {
	time = (GameM::getIns().getTime()-1) * 90.f;
}

inline void ClockObj::render(HDC _h, int _xOff, int _yOff) {
	int x = (int)p.x + _xOff, y = (int)p.y + _yOff;
	int w = (int)size.x, h = (int)size.y;
	int hSize = w >> 1;
	float _cos = cos(time * Deg2Rad) * -hSize;
	float _sin = sin(time * Deg2Rad) * hSize;
	Pos<float> center(x + (w >> 1), y + (h >> 1));


	HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(202,9,63));
	HBRUSH old = (HBRUSH)SelectObject(_h, brush);
	Pie(_h, x, y, x + w, y + h, center.x + (int)_sin, center.y + (int)_cos, center.x-1, y);
	SelectObject(_h, old);
	DeleteObject(brush);

	clockImg->AlphaBlend(_h, x, y, w, h, 0, 0, 29, 31, (BYTE)255, AC_SRC_OVER);
}
