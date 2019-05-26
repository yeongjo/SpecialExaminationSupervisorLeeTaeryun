#pragma once
#include "ClockObj.h"

class AnimSprite {
	int animDelayTimer;
	int spriteIdx;
	int spriteGroupIdx;
	int spriteSecondIdx;
	vector<vector<int>> animIdxGroup;
	Pos<> splitUV;

	vector<CImage *> animImgs;

	void goNextSpriteIdx();
public:
	AnimSprite();
	~AnimSprite();

	virtual void init(Pos<> _splitUV);

	void changeAnim(UINT i);

	virtual void render(HDC h, Pos<float>& p, Pos<float> &size);
};

