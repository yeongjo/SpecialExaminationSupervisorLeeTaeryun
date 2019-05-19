#pragma once
#include "MyMain.h"

class ClickObj;

// Singleton
// ��� Ŭ�������� ������Ʈ���� ����
class GameInputM : public Manager{
	friend class ClickObj;
	POINT mousePos;
	HWND hWnd;

	vector<ClickObj *> clickObjs;

	void addClickObj(ClickObj *obj) {
		clickObjs.push_back(obj);
	}

	void removeClickObj(ClickObj *obj);

	// ���콺 ��ġ �޾ƿ���
	void setMousePos();
public:
	static GameInputM s;
	GameInputM();
	~GameInputM();

	// Ŀ����ġ���Ҷ� �������ڵ� �ʿ�
	void init(HWND hWnd);
	
	POINT &getMousePos() { return mousePos; }

	// ���콺 ��ġ, Ŭ������ �巡�� ���� �˾Ƽ� �ؿ� �ִ� ��ü�鿡�� �˷��ֱ�
	virtual void tick();
};

