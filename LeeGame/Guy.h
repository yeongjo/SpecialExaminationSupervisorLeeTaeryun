#pragma once


#include "ClickObj.h"

// ���� �־����� ��ǥ������ ������
// ��ǥ������ ������ �����ϼ�����
// ��ǥ������ �־�� ���� ��
class Guy : public ClickObj {

	int remainDragStayTime;
public:
	Guy();
	~Guy();

	virtual void onceDown();
	virtual void stayDown();
	virtual void onceUp();

	virtual void drag();
};

// TODO Ŭ���Ҽ��ִ��� �������� �������̽��� ����ҵ�
// ���, ������ Ŭ������