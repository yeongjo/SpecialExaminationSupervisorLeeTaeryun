#pragma once
#include "Desk.h"

// 시간표시 Pie 함수
class ClockObj : public Obj{
	float time;
public:
	ClockObj(int x, int y);
	~ClockObj();

	virtual void update() {
		time+=0.1f;
	}

	virtual void render(HDC _h) {
		int x = (int)p.x, y = (int)p.y;
		int w = (int)size.x, h = (int)size.y;
		Pie(_h, x, y, w, h, 0,0,(int)time,(int)time);
	}
};

