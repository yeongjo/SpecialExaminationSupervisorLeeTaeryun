#pragma once
#include "Desk.h"


//class CImage;
// 시간표시 Pie 함수
class ClockObj : public Obj{
	float time;

	static CImage *clockImg;
public:
	ClockObj(int x, int y);
	~ClockObj();

	static void loadImg();

	virtual void tick();

	void render(HDC h) {}
	virtual void render(HDC _h, int _xOff, int _yOff);
};

