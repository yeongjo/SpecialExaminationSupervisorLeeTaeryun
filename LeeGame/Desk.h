#pragma once
#include "Guy.h"
class Student; class AnimSpriteByImages;
class Desk : public Obj{

	// TODO å�� �������� �ְ� �������� �ݰų� ��ü�Ҽ�����
	class TestPaper {
	public:
		// 0: ���
		// 2: ����Ʈ��
		// 2: �߸���� ��ü�ش޶��Ұ���
		int state = 0;
	};
	AnimSpriteByImages* anim;
	Student *sitStudent; // �ɾ��ִ� �л� �Ͼ���� ����
	// �л��� Desk �����ؼ� ����
public:
	TestPaper testPaper;

	Desk();
	~Desk();

	void changeTestPaperState(int state);

	// GameM���� ���� �л� �ޱ�
	// �л��� sitDesk�� �ڱ⸦ ��
	// ��ġ ������ �ؾ��ҵ�
	void init(Student *stu, int x, int y);

	void flip();

	Student *getStudent() { return sitStudent; }

	void render(HDC h);
};

