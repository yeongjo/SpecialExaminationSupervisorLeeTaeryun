#pragma once
#include "Guy.h"
class Student; class AnimSpriteByImages;
class Desk : public Obj{

	// TODO å�� �������� �ְ� �������� �ݰų� ��ü�Ҽ�����
	class TestPaper {
	public:
		// 0: ���
		// 1: ����Ʈ��
		// 2: �߸���� ��ü�ش޶��Ұ���
		int state = 0;
	};
	TestPaper testPaper;
	AnimSpriteByImages* anim;
	Student *sitStudent; // �ɾ��ִ� �л� �Ͼ���� ����
	// �л��� Desk �����ؼ� ����
public:
	Desk();
	~Desk();

	// GameM���� ���� �л� �ޱ�
	// �л��� sitDesk�� �ڱ⸦ ��
	// ��ġ ������ �ؾ��ҵ�
	void init(Student *stu, int x, int y);

	void flip();

	Student *getStudent() { return sitStudent; }

	void render(HDC h);
};

