#pragma once
#include "Guy.h"
class Student;
class Desk : public Obj{

	// TODO å�� �������� �ְ� �������� �ݰų� ��ü�Ҽ�����
	class TestPaper {
	public:
		bool isDrop; // ����Ʈ��
		bool isMess; // �߸���� ��ü�ش޶��Ұ���
	};
	TestPaper testPaper;

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
};

