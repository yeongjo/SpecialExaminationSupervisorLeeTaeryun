#pragma once

#include "GameInputM.h"

class ClickObj : public Obj{
protected:
	bool isDraging = false;
	bool isMouseDown = false;
	bool isMouseStay = false;
public:

	ClickObj();// GameInputM에 clickObjs에서 추가됨
	~ClickObj(); // GameInputM에 clickObjs에서 제거됨

	// 클릭할땐 ObjM에서 가장 마지막에 있는거부터 순서대로 검사해야함
	// 클릭검사하는거 넣어주기
	virtual bool isMouseOver(int x, int y);

	virtual void onceDown() = 0;
	virtual void stayDown() = 0;
	virtual void onceUp() = 0;

	bool getIsMouseDown() { return isMouseDown; }
	bool getIsMouseStay() { return isMouseStay; }

	// 그냥 조건 상관없이 업데이트에서 불러주기
	// 그래야 마우스가 나가도 드래그 되기때문
	virtual void drag() = 0;
};

