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

	GameoverBroadcastObj *broadcastGameover();
	PopMsgBroadcastObj *broadcastPopMsg(int idx, Pos<float>& _p, Student *stu);
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
		_alpha-=deltatime;
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
	bool isDelete =false;
	GameoverBroadcastObj() {
		if (img) return;
		img = new CImage();
		img->Load(L"img/게임오버.png");
	}
	void tick() {
		if(isDelete)
		BroadcastObj::tick();
	}
};

class PopMsgBroadcastObj : public GameoverBroadcastObj {
public:
	static CImage *roundImg [10];
	int _idx;
	Student *_stu;
	// 0 sleep
	// 1 paper change plz
	// 2 paper drop
	PopMsgBroadcastObj(int idx, Pos<float>& _p, Student *stu) {
		GameM::getIns().everyPopmsgForInitClear.push_back(this);
		p = _p;
		_stu = stu;
		p += Pos<float>(30, 0);
		_idx = idx;
		_alpha = 255;
		if (!roundImg [idx]) {
			roundImg [idx] = new CImage();
			wstringstream ss;
			ss << L"img/popmsg" << idx << L".png";
			roundImg [idx]->Load(ss.str().c_str());
		}
		p.y -= roundImg [idx]->GetHeight();
		off.x = GameM::getIns().getClassroom(0)->off.x;
	}
	~PopMsgBroadcastObj();
	void tick() {
		off.x = GameM::getIns().getClassroom(0)->off.x;
		GameoverBroadcastObj::tick();
	}
	void render(HDC h) {
		roundImg[_idx]->AlphaBlend(h, p.x + off.x, p.y+ off.y, alpha, AC_SRC_OVER);
	}
};