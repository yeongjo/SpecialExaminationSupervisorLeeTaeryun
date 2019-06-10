#pragma once
#include "AnimSpriteByImages.h"

class StudentState; class Classroom; class PopMsgBroadcastObj;

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
	

	Classroom *myClass; // ���ǿ� ���س�ĥ���ʿ�

	// 0 : ��� ����Ǫ�°� �ձ�ڱ��, ������ �ִ°� �߰����� ���
	// 1 : ������ �ִ°�
	// 2 : �Ӹ����°�

	static AnimSpriteByImages* preloadSprite[4];
	AnimSpriteByImages *sprite;

	Type type; // GameM�� init �Լ��� ���� ��������

	StudentState *state = nullptr;

	//	[�ۿ���] [18:11] int�� 1���� 100���� �����ϸ�
	//	[�ۿ���] [18:11] ���� ������ 1�� ������Ű�°Ŷ� �ָ��ϴϱ�
	//	[�ۿ���] [18:12] �׳� float [0 ~ 1] ������ �ص� �����Ѱ�

	// [0 ~ 1] ����
	float angryAmount;
	float angryUiSize = 85;

	bool isHisDeskFilped = false;
	int flipRemoveTimer = 1000;

public:
	// ��ġ �����Ҷ��� �ʿ�
	Desk *sitDesk; // ��������� �ʿ�
	PopMsgBroadcastObj *popMsgObj = nullptr;

	Student();
	~Student();

	static void loadImages();

	// �л� Ÿ���̶�, ���¼������ֱ�
	void init(Student::Type type, StudentState *state, Classroom *_class);

	void setState(StudentState *state);

	// Classroom ���Լ� ����
	// ��ó���� �� ȭ���� �ϴ� ����� ������ ��ġ����
	void takeAngryDamage(float amount);

	// TODO �̻�¡�� �ʱ�ȭ
	void resetState();

	// ȭ����ġ ����
	virtual void tick();

	// �ֺ��� �������� �����ֱ�
	void action();

	// Ȱ��ȭ�ؼ� �ֺ��� �����ְ��ϱ�
	// �̹�Ȱ��ȭ�������� false ��ȯ
	bool activeState();

	void angryFlipDesk();

	// ����ϴ� �Ҹ�, ��ǳ��
	void annoySound();

	virtual void render(HDC h);

	bool isDestroyZone();

	void removePopMsg();

	void onceDown() {
		Guy::onceDown();
		SoundM::studentDrop();
	}
	void onceUpWithOutMouseCheck();

	void popMsg(int idx);
	
	Classroom *getClassroom() { return myClass; }
	AnimSpriteByImages *getSprite() { return sprite; }

	float getAngryAmount() { return angryAmount; }

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
	// ������ �ٶ��� Ȱ��ȭ, �ذ��ϸ� ��Ȱ��ȭ
	bool isAble = false;
	// �Ҹ��� ����Ǵ��� �ѹ��� ����ҰŶ� ��
	bool isPlaying = false;
public:
	// �ٸ���� Ȥ�� ������ ���� ������ �ִ���
	// ���� �ִϸ��̼��� ��ŷ� �ٲ���� ���⼭ ����
	// �� �ȿ��� �������� �� �� �ϳ��� ������ �Ѵ�.
	// stu�� �� �Լ��� ������ ģ���� ��
	virtual void action(Student *stu);

	// Ȱ��ȭ �̹�Ȱ��ȭ�������� false ����
	virtual bool active(Student *stu);

	virtual bool _active(Student *stu) { return true; }

	// �����ذ������� ������ �����ذ�
	// �л����� Ŭ������ �巡�������� ���¸� �����´�.
	virtual void fixState(Student *stu);

	void alwaysFixState(Student *stu){
		isAble = false;
		isPlaying = false;
		stu->getSprite()->changeAnim(0);
	}


protected:
	virtual void fix(Student *stu) {
		alwaysFixState(stu);
	}
};

// ������ ��ü�ش޶��ϴ� ����
// ������ ������ ����
// �ڰ�� ����
// �Ӹ�����
// �ڰ���

class DropPaperStudentState : public StudentState {
public:
	DropPaperStudentState() { range = 0; amount = 0.05f; }
	bool _active(Student *stu) {
		SoundM::wantChangePaperSound();
		stu->popMsg(2);
		return true;
	}
	virtual void action(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		stu->sitDesk->changeTestPaperState(0);
		stu->removePopMsg();
	}
};

class WantChangePaperStudentState : public StudentState {
public:
	WantChangePaperStudentState() { range = 0; amount = 0.05f; }
	bool _active(Student *stu) {
		SoundM::wantChangePaperSound();
		stu->popMsg(1);
		return true;
	}
	virtual void action(Student *stu);
	virtual void fixState(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		stu->removePopMsg();
	}
};

class SleepStudentState : public StudentState {
public:
	SleepStudentState() { range = 300; amount = 0.02f; }
	bool _active(Student *stu) {
		stu->popMsg(0);
		return true;
	}
	virtual void action(Student *stu);
	//void fixState(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		SoundM::stopSleep();
		stu->removePopMsg();
	}
};

class DanceStudentState : public StudentState {
public:
	DanceStudentState() { range = 300; amount = 0.02f; }
	bool _active(Student *stu) {
		SoundM::headDance();
		return true;
	}
	virtual void action(Student *stu);
	//void fixState(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		SoundM::stopHeadDance();
	}
};

// Ư�� ����
class KindStudentState :public StudentState{
	virtual void action(Student *stu) {}
	virtual bool active(Student *stu) { return true; }
};

// �����ϱ�
class SpyStudentState : public StudentState {
	Student *targetStu;
public:
	SpyStudentState(Student *_targetStu) : targetStu(_targetStu){range = 0; amount = 0.1f;}
	virtual bool active(Student *stu) {
		bool _t = isAble;
		isAble = true;
		return !_t;
	}
	virtual void action(Student *stu);
};

class StudentStateMaker {
public:
	// �������� �� ���ÿ� �´� ���� �ѱ�
	static StudentState *makeNewState();
};