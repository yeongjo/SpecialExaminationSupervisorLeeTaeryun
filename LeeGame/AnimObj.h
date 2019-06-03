#pragma once
#include "ClockObj.h"

class AnimSprite {
	int animDelayTimer;
	bool isAnimEnd = false;
	int spriteIdx;
	int spriteGroupIdx;
	int spriteSecondIdx;
	// TODO 초기화할 방법을 찾아야함
	// -1이면 루프안돌리고 멈춤
	// -2면 다음에 나오는 인덱스로 애니메이션 전환
	// ex [0,1,2,-2,1] 0,1,2 재생후 1번 애니메이션 재생
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

