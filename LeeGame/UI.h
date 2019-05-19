#pragma once
#include "GameM.h"

// 다음교시로 넘어감을 알림
class UI {
public:
	UI();
	~UI();

	// 생각해보니 라운드 넘어가는 텍스트는 이미지로 할거같다
	void broadcastMain(wstring msg);
};

class BroadcastObj : public Obj {
public:
	virtual void render(HDC h) {

	}
};