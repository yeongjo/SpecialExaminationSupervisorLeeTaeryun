#pragma once
#include "AnimObj.h"

class StudentState; class Classroom;

// Classroom, GameM���� vector�� ����������

// �󸶳� ����ġ��ģ������ �¾�� ������
// �Ѹ��� �����̰� �ִ�.
// �̻�¡�� �߻� Ÿ�̹��� GameM���� ���ְ� �̻�¡�� �߻��� �л�����
class Student : public Guy {
	friend class Desk;
	friend class StudentState;
public:
	enum class Type;
private:
	// ��ġ �����Ҷ��� �ʿ�
	Desk *sitDesk; // ��������� �ʿ�

	Classroom *myClass; // ���ǿ� ���س�ĥ���ʿ�

	AnimSprite sprite; // TODO �ʱ�ȭ�ؾ��� ���� �ҷ����� set UV

	Type type; // GameM�� init �Լ��� ���� ��������

	StudentState *state;

	//	[�ۿ���] [18:11] int�� 1���� 100���� �����ϸ�
	//	[�ۿ���] [18:11] ���� ������ 1�� ������Ű�°Ŷ� �ָ��ϴϱ�
	//	[�ۿ���] [18:12] �׳� float [0 ~ 1] ������ �ص� �����Ѱ�

	// [0 ~ 1] ����
	float angryAmount;
public:
	Student();
	~Student();

	// �л� Ÿ���̶�, ���¼������ֱ�
	void init(Student::Type type, StudentState *state);

	void setState(StudentState *state);

	// Classroom ���Լ� ����
	// ��ó���� �� ȭ���� �ϴ� ����� ������ ��ġ����
	void takeAngryDamage(float amount);

	// ȭ����ġ ����
	virtual void tick();

	void angryFlipDesk();

	// ����ϴ� �Ҹ�
	void annoySound();

	virtual void onceDown();
	virtual void stayDown();

	virtual void render(HDC h);


	Classroom *getClassroom() { return myClass; }

	enum class Type {
		normal, //  ��
		spy, // �� �� �Ѹ�ۿ� ���� 
		kind // �ƹ��߸������� �������ü����
	};
};

// ��� �޸�
// ��©�� ���� �����ϰ� �� ���¸°Ը� �ൿ�ϰ��ұ�
// �׳� �÷��̾� �ȿ��� switch�� �� �ұ�
// ���ڷ� �ҷ�
//
// ������ �ڱ⿡�� �����ִ� �ൿ
//	������ ����,  ��ü, 
// ���鿡�� �����ִ� �ൿ
//	�Ӹ�����, �ڰ���, ������� �����ϱ�
//	�����ϱ�� *Student �޾ƿͼ� Ȯ���ϱ�
class StudentState {
	// ���Ⳣĥ ������ ��
	float range, amount;
public:
	// �ٸ���� Ȥ�� ������ ���� ������ �ִ���
	// ���� �ִϸ��̼��� ��ŷ� �ٲ���� ���⼭ ����
	virtual void action(Student *stu);
};

// Ư�� ����
class KindStudentState :public StudentState{
	virtual void action(Student *stu) {}
};

class SpyStudentState : public StudentState {
	virtual void action(Student *stu); // TODO �ִϸ��̼� �ε����� ���� �߰�����
};

class StudentStateMaker {
public:
	static StudentState *makeNewState(int i) {
		switch (i) {
		case 0:

			break;
		}
	}
};