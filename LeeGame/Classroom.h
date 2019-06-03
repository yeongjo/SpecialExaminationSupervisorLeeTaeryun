#pragma once

#include "Student.h"
using namespace std;

// ����

// GameM���� ����������

// �л��� 9���� �⺻

//�����¹���ǥ���������ְ�
//���Ǿȿ� �ִ� �л����� �����Ѵ�.
// �ʿ��ϸ� �� ���ǿ��� �����л� �߻���ٰ� �˷��ִ°ŵ� �����ҵ�

// �۷ι� ���� �Ҷ��� ���⼭ ��
// �۷ι� ����� �� ģ���� Ư�� �Լ��� �ҷ� ������ ������
// �ٸ� ��� �л��鿡�� ���ظ� ��
class Classroom : public Obj{
	// �л��� ��ӹ޴� �����ڰ� �����Ŷ� �����ͷ� ��
	vector<Student*> students;
	vector<Desk *> desks;
public:
	Classroom();
	~Classroom();

	/* TODO �̹��� �ҷ�����
	 �л� �� 9������ �ʱ�ȭ
	 ������ ������ ����
	 i�� ���� ��ġ�� x�������� ���� �����ŭ �з������ϱ�
	 */
	// �л��� å���� ��� �ʱ�ȭ��
	void init(int i);

	// �ٸ�������� ȭ�����ϰ������ ȣ��
	// stu���� �� ����� ������ ����� ȭ���� �Ѵ�. ������ ��������
	void makeAngryStudentInClass(Student *stu, float amount, float range);
	void makeAngryThisStuent(Student *stu, float amount);

	void removeStudent(int i);

	// TODO �̹��� �׸���
	virtual void render(HDC h);

	size_t getStudentSize();
	//�ڵ����� assert �Ǵϱ� ����
	Student *getStudent(int i) { return students [i]; }
};

