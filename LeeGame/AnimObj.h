#pragma once
#include "ClockObj.h"

class AnimSprite {
	int animDelayTimer;
	bool isAnimEnd = false;
	int spriteIdx;
	int spriteGroupIdx;
	int spriteSecondIdx;
	// TODO �ʱ�ȭ�� ����� ã�ƾ���
	// -1�̸� �����ȵ����� ����
	// -2�� ������ ������ �ε����� �ִϸ��̼� ��ȯ
	// ex [0,1,2,-2,1] 0,1,2 ����� 1�� �ִϸ��̼� ���
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

