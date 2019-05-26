#pragma once
#include "MyMain.h"

class ClickObj;

// Singleton
// ��� Ŭ�������� ������Ʈ���� ����
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

	// ���콺 ��ġ �޾ƿ���
	void setMousePos();
public:
	GameInputM();
	~GameInputM();

	// Ŀ����ġ���Ҷ� �������ڵ� �ʿ�
	void init(HWND hWnd,Pos<> *dbStartPos);
	
	POINT &getMousePos() { return mousePos; }

	// ���콺 ��ġ, Ŭ������ �巡�� ���� �˾Ƽ� �ؿ� �ִ� ��ü�鿡�� �˷��ֱ�
	virtual void tick();

	static GameInputM &getIns() {
		if (!s) s = new GameInputM();
		return *s;
	}
};

