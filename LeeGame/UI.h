#pragma once
#include "GameM.h"

class PopMsgBroadcastObj;
// 다음교시로 넘어감을 알림
class UI : public Singleton<UI> {
public:
	UI();
	~UI();

	// 생각해보니 라운드 넘어가는 텍스트는 이미지로 할거같다
	void broadcastMain(wstring msg);

	void broadcastRound(int round);

	void broadcastGameover();
	PopMsgBroadcastObj *broadcastPopMsg(int idx, Pos<float>& _p);
};

class BroadcastObj : public Obj {
protected:
	static CImage *img;
	float alpha = 255;
	float _alpha = 500;
public:
	BroadcastObj() :Obj(3) {
	}
	void tick() {
		alpha = _alpha > 255 ? 255 : _alpha;
		_alpha--;
		if (alpha < 0) delete this;
	}
	virtual void render(HDC h) {
		img->AlphaBlend(h, p.x, p.y, alpha, AC_SRC_OVER);
	}
};

class RoundBroadcastObj : public BroadcastObj {
public:
	int _round;
	static CImage *roundImg [3];
	RoundBroadcastObj(int round) {
		_round = round;
		if (roundImg [round]) return;
		
		img = new CImage();
		wstringstream ss;
		ss << L"round" << round << L".png";
		img->Load(ss.str().c_str());
	}
	void render(HDC h) {
		roundImg[_round-1]->AlphaBlend(h, p.x, p.y, alpha, AC_SRC_OVER);
		//img->AlphaBlend(h, p.x, p.y, alpha, AC_SRC_OVER);
	}
};
class GameoverBroadcastObj : public BroadcastObj {
public:
	GameoverBroadcastObj() {
		if (img) return;
		img = new CImage();
		img->Load(L"gameover.jpg");
	}
};

class PopMsgBroadcastObj : public BroadcastObj {
public:
	static CImage *roundImg [10];
	int _idx;
	bool isDelete;

	// 0 sleep
	// 1 paperplz
	PopMsgBroadcastObj(int idx, Pos<float>& _p) {
		if (roundImg[idx]) return;
		_idx = idx;
		_alpha = 255;
		roundImg[idx] = new CImage();
		wstringstream ss;
		ss << L"round" << idx << L".png";
		roundImg[idx]->Load(ss.str().c_str());
	}
	void tick() {
		if(isDelete)
		BroadcastObj::tick();
	}
	void render(HDC h) {
		roundImg[_idx]->AlphaBlend(h, p.x, p.y, alpha, AC_SRC_OVER);
	}
};