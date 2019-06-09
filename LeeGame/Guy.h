#pragma once


#include "ClickObj.h"

// ���� �־����� ��ǥ������ ������
// ��ǥ������ ������ �����ϼ�����
// ��ǥ������ �־�� ���� ��
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

	// ����ϸ� �ν����°�
	virtual bool isDestroyZone() = 0;
};

// TODO Ŭ���Ҽ��ִ��� �������� �������̽��� ����ҵ�
// ���, ������ Ŭ������