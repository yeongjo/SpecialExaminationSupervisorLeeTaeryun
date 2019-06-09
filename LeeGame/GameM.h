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

	int giveAngryTimer = -1;
	int roundStartDelayTimer = 0; // ��������Ҷ����� ��� �̻�¡�ľ��� �����ϰ��Ϸ��� ����

	vector<CImage *>roundImgs;
	int roundTimer;

	int angryDelay = 3000;

	bool isEnd = false;

	int classroomSizeX = 464*2;
	int watchClassIdx = 0;
	float lerpOffX = 0;

	int flipStudentCount;

	CImage *gameoverImg = nullptr;

public:
	bool isGamePlayScene = true;
	
	GameM();
	~GameM();

	void loadImg();

	// ���ǰ� �л�, �ð� �ʱ�ȭ
	void init();

	// �ð��帣���ϰ� ���ð� ������ �л��� �г��ġ ��ȭ��
	// �ܰ躰�� ���ʿ� �ѹ��� �̻�¡�� �߻��ϴ���
	void update();

	// �г��ġ �ʱ�ȭ �� ��� �̻���¿��� ���ƿ���
	void nextPeriodEffect();

	// ���� �ð��� ������ �л����߿� �Ѹ��� �̻�¡�İ���
	void giveWithDelayAngry();

	void broadcastRound(int round);
	
	void gameover();

	void increaseFlipStudent();
	float getTime() { return time; }
	int getPeriod() { return period; }
	size_t getStudentSize();
	//Student *getStudent(int idx);
	Classroom *getClassroom(int i) { return &classrooms [i]; }
};

