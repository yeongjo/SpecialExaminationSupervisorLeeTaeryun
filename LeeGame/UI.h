#pragma once
#include "GameM.h"

// �������÷� �Ѿ�� �˸�
class UI {
public:
	UI();
	~UI();

	// �����غ��� ���� �Ѿ�� �ؽ�Ʈ�� �̹����� �ҰŰ���
	void broadcastMain(wstring msg);
};

class BroadcastObj : public Obj {
public:
	virtual void render(HDC h) {

	}
};