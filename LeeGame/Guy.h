#pragma once


#include "ClickObj.h"

// 일을 주어지면 목표지점을 지정함
// 목표지점이 있으면 움직일수있음
// 목표지점에 있어야 일을 함
class Guy : public ClickObj {

	int remainDragStayTime;
	Pos<float> prevDragPos;
public:
	Guy();
	~Guy();

	virtual void onceDown();
	virtual void stayDown();
	virtual void onceUp();

	virtual void drag();

	// 드랍하면 부숴지는곳
	virtual bool isDestroyZone() = 0;
};

// TODO 클릭할수있는지 없는지를 인터페이스로 써야할듯
// 사람, 시험지 클릭가능