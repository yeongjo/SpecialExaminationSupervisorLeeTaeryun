#pragma once
#include "GameM.h"

// �������÷� �Ѿ�� �˸�
class UI : public Singleton<UI> {
public:
	UI();
	~UI();

	// �����غ��� ���� �Ѿ�� �ؽ�Ʈ�� �̹����� �ҰŰ���
	void broadcastMain(wstring msg);

	void broadcastRound(int round);
};

class BroadcastObj : public Obj {
	CImage *img;
	float alpha = 255;
	float _alpha = 500;
public:
	BroadcastObj(int round) :Obj(3) {
		img = new CImage();
		wstringstream ss;
		ss << L"round" << round << L".png";
		img->Load(ss.str().c_str());
	}
	void tick() {
		alpha = _alpha > 255 ? 255 : _alpha;
		if (alpha < 0) delete this;
	}
	virtual void render(HDC h) {
		//img->AlphaBlend(h, p.x, p.y, alpha, AC_SRC_OVER);
	}
};