#pragma once
#include "MyMain.h"

class ClickObj;

// Singleton
// 모든 클릭가능한 오브젝트들을 관리
class GameInputM : public Manager{
	friend class ClickObj;
	static GameInputM *s;
	POINT mousePos;
	HWND hWnd;

	vector<ClickObj *> clickObjs;

	Pos<> *dbStartPos;

	void addClickObj(ClickObj *obj) {
		clickObjs.push_back(obj);
	}

	void removeClickObj(ClickObj *obj);

	// 마우스 위치 받아오기
	void setMousePos();
public:
	GameInputM();
	~GameInputM();

	// 커서위치구할때 윈도우핸들 필요
	void init(HWND hWnd,Pos<> *dbStartPos);
	
	POINT &getMousePos() { return mousePos; }

	// 마우스 위치, 클릭여부 드래그 여부 알아서 밑에 있는 객체들에게 알려주기
	virtual void tick();

	static GameInputM &getIns() {
		if (!s) s = new GameInputM();
		return *s;
	}
};

