#pragma once
#include "Desk.h"

// 시간표시 Pie 함수
class ClockObj : public Obj{
	float time;
public:
	ClockObj(int x, int y);
	~ClockObj();

	virtual void update() {
		time+=1.f;
	}

	virtual void render(HDC _h) {
		int x = (int)p.x, y = (int)p.y;
		int w = (int)size.x, h = (int)size.y;
		int hSize = w >> 2;
		float _cos = cos(time * PI / 180)*hSize;
		float _sin = sin(time * PI / 180)*hSize;
		Pos<float> center(x + (w >> 2), y + (h >> 2));
		Pie(_h, x, y, x+w, y+h, center.x, center.y, (int)_cos,(int)_sin);
	}
};

