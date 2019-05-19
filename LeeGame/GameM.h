#pragma once

#include "Classroom.h"
#include "Singleton.h"

// ���� ������
// ����, �ð�, �л� ����
class GameM : public Singleton<GameM>{
	
	int period;// ���� [ 1���� ���� ]
	float time; // ���� �ð� [ 1 -> 2 ] ���̸� 1�����̰� 2���÷� ��������

	// ���⼭�� �����ͷ� ������ �ϰ� ���ǿ��� ������ �������
	vector<Student*> students; // ���Ǿȿ� �ִ� ��� �л���
	// �л����� ���Ǻ��� ���� ������ �������־���ұ�
	// �׷��� ���ǿ��� �����°� ���鶧 �����ҵ�

	vector<Classroom> classrooms;

	clock_t begin, passClock;
public:
	GameM();
	~GameM();

	// ���ǰ� �л�, �ð� �ʱ�ȭ
	void init();

	// �ð��帣���ϰ� ���ð� ������ �л��� �г��ġ ��ȭ��
	void update();

	void nextPeriodEffect();

	float getTime() { return time; }
	int getPeriod() { return period; }
	Student *getStudent(int idx) { return students [idx]; }
	Classroom *getClassroom(int i) { return &classrooms [i]; }
};

