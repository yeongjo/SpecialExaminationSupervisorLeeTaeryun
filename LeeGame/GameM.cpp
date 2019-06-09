#include "GameM.h"
#include "MTimer.h"
#include "UI.h"
#include "SoundM.h"
//#define TEST

GameM::GameM() {
	SoundM::init();

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
#ifdef TEST
	ranClass = 1;
#endif
	SpyStudentState *spy;
	if (ranStudent % 3 == 0) { // �������
		spy = new SpyStudentState(classrooms [ranClass].getStudent(ranStudent+1));
	}else if (ranStudent % 3 - 2 == 0) { // ���������
		spy = new SpyStudentState(classrooms [ranClass].getStudent(ranStudent-1));
	} else {
		spy = new SpyStudentState(classrooms [ranClass].getStudent(ranStudent-1));
	}

	classrooms [ranClass].getStudent(ranStudent)->init(
		Student::Type::spy, spy, &classrooms [ranClass]);

	begin = clock();

	broadcastRound(1);

	
	if (MTimer::isHere(giveAngryTimer)) {
		MTimer::reset(giveAngryTimer);
	} else {
		giveAngryTimer = MTimer::create(angryDelay, true, false);
	}
}

void GameM::update() {
	SoundM::update();
	SceneM::getIns(0).tick();
	if (isEnd) return;
	//passClock = clock() - begin;
	passClock += deltatime;
	// 1sec : passClock * 0.001f
	// 60sec : 1sec / 60
	//time = 1 + passClock * 0.001f / 60.f;
	time = 1 + passClock * 0.001f / 10.f;


	roundStartDelayTimer += deltatime;
	giveWithDelayAngry();

	// �������÷� �Ѿ
	if (period + 1 <= (int)time) {
		DBOUT(period << L"���� ��\n")
		if (period == 4) { // 4���ð� �� ����
			isEnd = true;
			return;
		}
		period++;
		roundStartDelayTimer = 0;
		angryDelay -= 500;
		MTimer::changeEndTime(giveAngryTimer, angryDelay);
		// TODO UI�� �������÷� �Ѿ�� ������
		// �л� �г��ġ ����
		// TODO ���氡���� ��ġ �л��� ���帶�� �����ϴ� �г� 30�� ����
		nextPeriodEffect();
	}

	// key
	// a
	if (KeyM::GetInst()->OnceKeyDown(0x41)) {
		if (watchClassIdx != -1) watchClassIdx--;
		lerpOffX = -classroomSizeX*watchClassIdx;
	//d
	}else if (KeyM::GetInst()->OnceKeyDown(0x44)) {
		if (watchClassIdx != 1) watchClassIdx++;
		lerpOffX = -classroomSizeX*watchClassIdx;
		
	}
	for (size_t i = 0; i < classrooms.size(); i++) {
		float _off = (lerpOffX - classrooms [i].off.x)*.1f;
		classrooms [i].changeOffX(_off);
	}
}

void GameM::nextPeriodEffect() {
	/*auto size = getStudentSize();
	for (size_t i = 0; i < size; i++) {
		auto stu = getStudent(i);
		stu->takeAngryDamage(-30);
		stu->resetState();
	}*/
	for (size_t i = 0; i < classrooms.size(); i++) {
		for (size_t j = 0; j < classrooms[i].getStudentSize(); j++) {
			auto _t = classrooms [i].getStudent(j);
			_t->takeAngryDamage(-.1f);
			_t->resetState();
		}
	}
}

void GameM::giveWithDelayAngry() {
	if (roundStartDelayTimer > 3000)
	if (MTimer::isEnd(giveAngryTimer)) {
		int rndClass = random(3);
		int _stuSize = classrooms [rndClass].getStudentSize();
		vector<int> rndStudent = unDuplicateRandom(_stuSize, _stuSize);
#ifdef TEST
		rndClass = 1;
		_stuSize = classrooms [rndClass].getStudentSize();
		rndStudent = unDuplicateRandom(_stuSize, _stuSize);
#endif
		for (size_t i = 0; i < _stuSize; i++) {
			auto _stu = classrooms [rndClass].getStudent(rndStudent[i]);
			if (_stu != nullptr && _stu->activeState()) {
				break;
			}
		}

		for (size_t i = 0; i < classrooms.size(); i++) {
		for (size_t j = 0; j < classrooms[i].getStudentSize(); j++) {
			auto _stu = classrooms [i].getStudent(j);
			_stu->action();
		}
	}
	}
	
}

void GameM::broadcastRound(int round) {
	UI::getIns().broadcastRound(round);
}

size_t GameM::getStudentSize() {
	size_t size = 0;
	for (size_t i = 0; i < classrooms.size(); i++) {
		size += classrooms [i].getStudentSize();
	}
	return size;
}

//Student *GameM::getStudent(int idx) {
//	for (size_t i = 0; i < classrooms.size(); i++) {
//		auto _stuSize = classrooms [i].getStudentSize();
//		if (idx - _stuSize < 0) {
//			return classrooms [i].getStudent(idx);
//		}
//		idx -= _stuSize;
//	}
//}
