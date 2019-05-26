#pragma once

#include "Classroom.h"
#include "Singleton.h"

// ���� ������
// ����, �ð�, �л� ����
class GameM : public Singleton<GameM>{
	
	int period;// ���� [ 1���� ���� ]
	float time; // ���� �ð� [ 1 -> 2 ] ���̸� 1�����̰� 2���÷� ��������

	// �л����� ���Ǻ��� ���� ������ �������־���ұ�
	// �׷��� ���ǿ��� �����°� ���鶧 �����ҵ�

	vector<Classroom> classrooms;

	clock_t begin, passClock;

	int giveAngryTimer;
public:
	GameM();
	~GameM();

	// ���ǰ� �л�, �ð� �ʱ�ȭ
	void init();

	// �ð��帣���ϰ� ���ð� ������ �л��� �г��ġ ��ȭ��
	// �ܰ躰�� ���ʿ� �ѹ��� �̻�¡�� �߻��ϴ���
	void update();

	// �г��ġ �ʱ�ȭ �� ��� �̻���¿��� ���ƿ���
	void nextPeriodEffect();

	// ���� �ð��� ������ �л����߿� �Ѹ��� �̻�¡�İ���
	void giveWithDelayAngry();
	
	float getTime() { return time; }
	int getPeriod() { return period; }
	size_t getStudentSize();
	Student *getStudent(int idx);
	Classroom *getClassroom(int i) { return &classrooms [i]; }
};

