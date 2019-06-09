#pragma once
#include "AnimObj.h"

// init, tick �ʼ�
class FrameBlock {
	int t_delayTime;
public:
	CImage *img;
	int delayTime;

	FrameBlock(CImage *_img, int _delayTime) : img(_img), delayTime(_delayTime){
	}

	// �����̰� ������ ���� �ð� ��ȯ
	// ������������ 0 ��ȯ
	int update(int deltaTime) {
		int minusNum;
		t_delayTime -= deltaTime;
		minusNum = t_delayTime;
		if (minusNum < 0) {
			t_delayTime = delayTime;
			return -minusNum;
		}
		return 0;
	}
};

class AnimSpriteByImages :
	public AnimSprite {

	// ������ ��ü ���� -1 -2�� �ᵵ�ǳ�
	//imgs[imgIdx][subImgIdx] = (FrameBlock*)-1;
	vector<vector<FrameBlock *>> imgs;
	UINT imgIdx = 0, subImgIdx = 0;

	static BLENDFUNCTION blend;
public:
	void init(vector<vector<wstring>> &imgNames);
	// �ð��� ������ �ڵ����� �����ִϸ��̼�����
	virtual void tick(int deltaTime);
	virtual void changeAnim(UINT i);
	virtual void render(HDC h, Pos<float>& p, Pos<float> &size);
};

