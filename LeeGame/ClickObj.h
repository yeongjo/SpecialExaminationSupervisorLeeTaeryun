#pragma once

#include "GameInputM.h"

class ClickObj : public Obj{
protected:
	bool isDraging = false;
	bool isMouseDown = false;
	bool isMouseStay = false;
public:

	ClickObj();// GameInputM�� clickObjs���� �߰���
	~ClickObj(); // GameInputM�� clickObjs���� ���ŵ�

	// Ŭ���Ҷ� ObjM���� ���� �������� �ִ°ź��� ������� �˻��ؾ���
	// Ŭ���˻��ϴ°� �־��ֱ�
	virtual bool isMouseOver(int x, int y);

	virtual void onceDown() = 0;
	virtual void stayDown() = 0;
	virtual void onceUp() = 0;

	bool getIsMouseDown() { return isMouseDown; }
	bool getIsMouseStay() { return isMouseStay; }

	// �׳� ���� ������� ������Ʈ���� �ҷ��ֱ�
	// �׷��� ���콺�� ������ �巡�� �Ǳ⶧��
	virtual void drag() = 0;
};

