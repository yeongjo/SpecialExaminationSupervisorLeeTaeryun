#include "GameM.h"



GameM::GameM() {
	init();
}


GameM::~GameM() {
}

void GameM::init() {
	period = 1;
	time = 1;
	// 교실사이즈 3고정
	classrooms.resize(3);
	for (size_t i = 0; i < classrooms.size(); i++) {
		classrooms [i].init(i);
	}
	// 교실에 평범한 친구들을 다 넣고 이제 스파이 넣어야 함
	int ranClass = rand() % 3;
	int ranStudent = rand() % 9;

	classrooms [ranClass].getStudent(ranStudent)->init(Student::Type::spy, new SpyStudentState());

	begin = clock();
}

void GameM::update() {
	passClock = clock() - begin;
	// 1sec : passClock * 0.001f
	// 60sec : 1sec / 60
	time = 1 + passClock * 0.001f / 60.f;

	// 다음교시로 넘어감
	if (period + 1 <= (int)time) {
		// UI로 다음교시로 넘어간걸 보여줌
		// 학생 분노수치 감소
		// TODO 변경가능한 수치 학생들 라운드마다 감소하는 분노 30퍼 정도
		nextPeriodEffect();
	}
}

void GameM::nextPeriodEffect() {
	for (size_t i = 0; i < students.size(); i++) {
		students [i]->takeAngryDamage(30);
	}
}
