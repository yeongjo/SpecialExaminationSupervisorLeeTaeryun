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

	// 0 : ��� ����Ǫ�°� �ձ�ڱ��, ������ �ִ°� �߰����� ���
	// 1 : ������ �ִ°�
	// 2 : �Ӹ����°�

	AnimSprite sprite; // TODO �ʱ�ȭ�ؾ��� ���� �ҷ����� set UV

	Type type; // GameM�� init �Լ��� ���� ��������

	StudentState *state = nullptr;

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

	// TODO �̻�¡�� �ʱ�ȭ
	void resetState();

	// ȭ����ġ ����
	virtual void tick();

	void angryFlipDesk();

	// ����ϴ� �Ҹ�, ��ǳ��
	void annoySound();

	virtual void onceDown();
	virtual void stayDown();
	virtual void onceUp();

	virtual void render(HDC h);

	
	Classroom *getClassroom() { return myClass; }
	AnimSprite *getSprite() { return &sprite; }

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

/* �Ź� ��ü�ϰ� �����ϴ½����� �ұ�
�׷��� ����ģ���� ����������� ���� */
class StudentState {
protected:
	// �������
	//StudentStateMaker �� GameM���� ���¸������
	StudentState *myState;
	// ���Ⳣĥ ������ ��
	float range, amount;
	bool isAble = true;
public:
	// �ٸ���� Ȥ�� ������ ���� ������ �ִ���
	// ���� �ִϸ��̼��� ��ŷ� �ٲ���� ���⼭ ����
	// �� �ȿ��� �������� �� �� �ϳ��� ������ �Ѵ�.
	// stu�� �� �Լ��� ������ ģ���� ��
	virtual void action(Student *stu);

	// �����ذ������� ������ �����ذ�
	// �л����� Ŭ������ �巡�������� ���¸� �����´�.
	void fixState(Student *stu);
};

// ������ ��ü�ش޶��ϴ� ����
// ������ ������ ����
// �ڰ�� ����
// �Ӹ�����
// �ڰ���

class DropPaperStudentState : public StudentState {
public:
	DropPaperStudentState() { range = 0; amount = 0.01f; }
	virtual void action(Student *stu);
	void fixState(Student *stu);
};

class WantChangePaperStudentState : public DropPaperStudentState {
public:
	WantChangePaperStudentState() { range = 0; amount = 0.01f; }
	virtual void action(Student *stu);
	void fixState(Student *stu);
};

// Ư�� ����
class KindStudentState :public StudentState{
	virtual void action(Student *stu) {}
};

// �����ϱ�
class SpyStudentState : public StudentState {
	Student *targetStu;
public:
	virtual void action(Student *stu); // TODO �ִϸ��̼� �ε����� ���� �߰�����
};

class StudentStateMaker {
public:
	// �������� �� ���ÿ� �´� ���� �ѱ�
	static StudentState *makeNewState(int period) {
		float ran = random();
		int period = GameM::getIns().getPeriod();
		switch (period) {
		case 1:
			return new DropPaperStudentState();
			break;
		case 2:
			if (ran < .3f) {
				return new DropPaperStudentState();
			} else if (ran < .6f) {
				return new DropPaperStudentState();
			}
			break;
		case 3:
			break;
		case 4:
			break;
		}
		
		
	}
};