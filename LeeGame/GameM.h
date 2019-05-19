#pragma once

#include "Classroom.h"
#include "Singleton.h"

// 게임 관리자
// 교시, 시간, 학생 관리
class GameM : public Singleton<GameM>{
	
	int period;// 교시 [ 1부터 시작 ]
	float time; // 지난 시간 [ 1 -> 2 ] 사이면 1교시이고 2교시로 가는중임

	// 여기서는 포인터로 참조만 하고 교실에서 실제로 들고있음
	vector<Student*> students; // 교실안에 있는 모든 학생들
	// 학생들은 교실별로 따로 교실이 가지고있어야할까
	// 그래야 교실에서 나가는거 만들때 수월할듯

	vector<Classroom> classrooms;

	clock_t begin, passClock;
public:
	GameM();
	~GameM();

	// 교실과 학생, 시간 초기화
	void init();

	// 시간흐르게하고 교시가 지나면 학생들 분노수치 완화함
	void update();

	void nextPeriodEffect();

	float getTime() { return time; }
	int getPeriod() { return period; }
	Student *getStudent(int idx) { return students [idx]; }
	Classroom *getClassroom(int i) { return &classrooms [i]; }
};

