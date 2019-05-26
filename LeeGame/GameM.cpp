#include "GameM.h"



GameM::GameM() {
}


GameM::~GameM() {
}

void GameM::init() {
	period = 1;
	time = 1;
	// ���ǻ����� 3����
	classrooms.resize(3);
	for (size_t i = 0; i < classrooms.size(); i++) {
		classrooms [i].init(i);
	}
	// ���ǿ� ����� ģ������ �� �ְ� ���� ������ �־�� ��
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

	// �������÷� �Ѿ
	if (period + 1 <= (int)time) {
		// UI�� �������÷� �Ѿ�� ������
		// �л� �г��ġ ����
		// TODO ���氡���� ��ġ �л��� ���帶�� �����ϴ� �г� 30�� ����
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
