#pragma once
#include "AnimObj.h"

// init, tick 필수
class FrameBlock {
	int t_delayTime;
public:
	CImage *img;
	int delayTime;

	FrameBlock(CImage *_img, int _delayTime) : img(_img), delayTime(_delayTime){
	}

	// 딜레이가 끝나면 남은 시간 반환
	// 끝나지않으면 0 반환
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

	// 포인터 자체 값을 -1 -2로 써도되나
	//imgs[imgIdx][subImgIdx] = (FrameBlock*)-1;
	vector<vector<FrameBlock *>> imgs;
	UINT imgIdx = 0, subImgIdx = 0;

	static BLENDFUNCTION blend;
public:
	void init(vector<vector<wstring>> &imgNames);
	// 시간이 지나면 자동으로 다음애니메이션으로
	virtual void tick(int deltaTime);
	virtual void changeAnim(UINT i);
	virtual void render(HDC h, Pos<float>& p, Pos<float> &size);
};

