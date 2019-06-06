#pragma once
#include "AnimObj.h"
class AnimSpriteSheet :
	public AnimSprite {
	int animDelayTimer;
	bool isAnimEnd = false;
	int spriteIdx;
	int spriteGroupIdx;
	int spriteSecondIdx;
	// TODO 초기화할 방법을 찾아야함
	// -1이면 루프안돌리고 멈춤
	vector<vector<int>> animIdxGroup;
	Pos<> splitUV;

	vector<CImage *> animImgs;

	void goNextSpriteIdx();
public:
	void init(Pos<> _splitUV);

	void changeAnim(UINT i);

	virtual void render(HDC h, Pos<float>& p, Pos<float> &size);
};

