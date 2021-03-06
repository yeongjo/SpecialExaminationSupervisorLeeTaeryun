#pragma once

#include "Classroom.h"
#include "Singleton.h"

class GameoverBroadcastObj;
class PopMsgBroadcastObj;
class FinalScene;

// 게임 관리자
// 교시, 시간, 학생 관리
class GameM : public Singleton<GameM>{
	
	int period;// 교시 [ 1부터 시작 ]
	float time; // 지난 시간 [ 1 -> 2 ] 사이면 1교시이고 2교시로 가는중임

	// 학생들은 교실별로 따로 교실이 가지고있어야할까
	// 그래야 교실에서 나가는거 만들때 수월할듯

	vector<Classroom> classrooms;


	clock_t begin, passClock;

	int giveAngryTimer = -1;
	int roundStartDelayTimer = 0; // 라운드시작할때마다 얘들 이상징후없이 시작하게하려고 만듬

	vector<CImage *>roundImgs;
	int roundTimer;

	int angryDelay;

	// 0 : 플레이중
	// 1 : 죽음
	// 2: 클리어
	int isEnd;

	int classroomSizeX = 464*2;
	int watchClassIdx = 0;
	float lerpOffX = 0;

	int flipStudentCount;
	int getoutCount;

	GameoverBroadcastObj *gameoverObj;
public:
	vector<PopMsgBroadcastObj *> everyPopmsgForInitClear;
	bool isGamePlayScene = false;

	FinalScene *finalScene;
	
	GameM();
	~GameM();

	// 교실과 학생, 시간 초기화
	void init();

	// 시간흐르게하고 교시가 지나면 학생들 분노수치 완화함
	// 단계별로 몇초에 한번씩 이상징후 발생하는지
	void update();

	// 분노수치 초기화 및 얘들 이상상태에서 돌아오게
	void nextPeriodEffect();

	// 일정 시간이 지나면 학생들중에 한명이 이상징후가짐
	void giveWithDelayAngry();

	void broadcastRound(int round);
	
	void gameover();

	void goMainScene() {
		init();
	}

	int calculateClearScore();

	void stu_getout();

	void increaseFlipStudent();
	float getTime() { return time; }
	int getPeriod() { return period; }
	size_t getStudentSize();
	//Student *getStudent(int idx);
	Classroom *getClassroom(int i) { return &classrooms [i]; }
};

