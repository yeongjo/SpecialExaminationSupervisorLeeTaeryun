#pragma once
#include "ClockObj.h"

class AnimSprite {
public:
	AnimSprite();
	~AnimSprite();


	virtual void changeAnim(UINT i) {}

	virtual void render(HDC h, Pos<float> &p, Pos<float> &size) {}
};

