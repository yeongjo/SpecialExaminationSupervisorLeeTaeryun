#pragma once
#include "AnimObj.h"
class AnimSpriteSheet :
	public AnimSprite {
	int animDelayTimer;
	bool isAnimEnd = false;
	int spriteIdx;
	int spriteGroupIdx;
	int spriteSecondIdx;
	// TODO �ʱ�ȭ�� ����� ã�ƾ���
	// -1�̸� �����ȵ����� ����
	vector<vector<int>> animIdxGroup;
	Pos<> splitUV;

	vector<CImage *> animImgs;

	void goNextSpriteIdx();
public:
	void init(Pos<> _splitUV);

	void changeAnim(UINT i);

	virtual void render(HDC h, Pos<float>& p, Pos<float> &size);
};

