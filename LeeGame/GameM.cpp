#include "GameM.h"



GameM::GameM() {
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

	if (MTimer::isHere(giveAngryTimer)) {
		MTimer::reset(giveAngryTimer);
	}
}

void GameM::update() {
	passClock = clock() - begin;
	// 1sec : passClock * 0.001f
	// 60sec : 1sec / 60
	time = 1 + passClock * 0.001f / 60.f;

	SceneM::getIns(0).tick();

	// 다음교시로 넘어감
	if (period + 1 <= (int)time) {
		// UI로 다음교시로 넘어간걸 보여줌
		// 학생 분노수치 감소
		// TODO 변경가능한 수치 학생들 라운드마다 감소하는 분노 30퍼 정도
		nextPeriodEffect();
	}
}

void GameM::nextPeriodEffect() {
	auto size = getStudentSize();
	for (size_t i = 0; i < size; i++) {
		auto stu = getStudent(i);
		stu->takeAngryDamage(-30);
		stu->resetState();
	}
}

void GameM::giveWithDelayAngry() {
	if (MTimer::isEnd(giveAngryTimer)) {

	}
}

size_t GameM::getStudentSize() {
	size_t size = 0;
	for (size_t i = 0; i < classrooms.size(); i++) {
		size += classrooms [i].getStudentSize();
	}
}

Student *GameM::getStudent(int idx) {
	return classrooms [idx / 9].getStudent(idx%9);
}
