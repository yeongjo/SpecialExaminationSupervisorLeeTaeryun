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
	getoutCount = flipStudentCount = 0;
	isEnd = 0;
	period = 1;
	time = 1;
	passClock = 0;

	//for (size_t i = 0; i < everyPopmsgForInitClear.size(); i++) {
	//	delete everyPopmsgForInitClear [i];
	//}
	//everyPopmsgForInitClear.clear();

	// 교실사이즈 3고정
	classrooms.resize(3);
	for (size_t i = 0; i < classrooms.size(); i++) {
		classrooms [i].init(i);
	}
	// 교실에 평범한 친구들을 다 넣고 이제 스파이 넣어야 함
	int ranClass = rand() % 3;
	int ranStudent = rand() % 9;
#ifdef TEST
	ranClass = 1;
#endif
	SpyStudentState *spy;
	if (ranStudent % 3 == 0) { // 가장왼쪽
		spy = new SpyStudentState(classrooms [ranClass].getStudent(ranStudent+1));
	}else if (ranStudent % 3 - 2 == 0) { // 가장오른쪽
		spy = new SpyStudentState(classrooms [ranClass].getStudent(ranStudent-1));
	} else {
		spy = new SpyStudentState(classrooms [ranClass].getStudent(ranStudent-1));
	}

	classrooms [ranClass].getStudent(ranStudent)->init(
		Student::Type::spy, spy, &classrooms [ranClass]);

	begin = clock();

	broadcastRound(1);

	
	angryDelay = 3000;
	if (MTimer::isHere(giveAngryTimer)) {
		MTimer::reset(giveAngryTimer);
		MTimer::changeEndTime(giveAngryTimer, angryDelay);
	} else {
		giveAngryTimer = MTimer::create(angryDelay, true, false);
	}
}

void GameM::update() {
	if (!isGamePlayScene) return;

	if (isEnd == 1 && KeyM::GetInst()->OnceKeyUp(VK_RBUTTON)) {
		gameoverObj->isDelete = true;
		init();
	}
	if (isEnd == 2) {
		if (KeyM::GetInst()->OnceKeyUp(VK_RBUTTON))
			isGamePlayScene = true;
		return;
	}
	SoundM::update();

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
		float _off = (lerpOffX - classrooms [i].off.x)*.15f;
		classrooms [i].changeOffX(_off);
	}
	SceneM::tick();
	if (isEnd) return;
	//passClock = clock() - begin;
	passClock += deltatime;
	// 1sec : passClock * 0.001f
	// 60sec : 1sec / 60
	//time = 1 + passClock * 0.001f / 60.f;
	// -----------------시간바꾸는곳-------------------------------
	time = 1 + passClock * 0.001f / 20.f;
	// ------------------------------------------------------------------------------


	roundStartDelayTimer += deltatime;
	giveWithDelayAngry();

	// 다음교시로 넘어감
	if (period + 1 <= (int)time) {
		DBOUT(period << L"교시 끝\n")
		if (period == 4) { // 4교시가 다 끝남
			isEnd = 2;
			SceneM::changeScene(1);
			return;
		}
		period++;
		roundStartDelayTimer = 0;
		angryDelay -= 800;
		MTimer::changeEndTime(giveAngryTimer, angryDelay);
		// TODO UI로 다음교시로 넘어간걸 보여줌
		// 학생 분노수치 감소
		// TODO 변경가능한 수치 학생들 라운드마다 감소하는 분노 30퍼 정도
		nextPeriodEffect();
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
				DBOUT(_stu << L"activeState\n");
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

void GameM::gameover() {
	if (isEnd) return;
	gameoverObj = UI::getIns().broadcastGameover();
	isEnd = 1;
}

int GameM::calculateClearScore() {
	float count = flipStudentCount*100 - getoutCount*50;
	float totalAngry = 0;
	for (size_t i = 0; i < classrooms.size(); i++) {
		for (size_t j = 0; j < classrooms[i].getStudentSize(); j++) {
			totalAngry += classrooms [i].getStudent(j)->getAngryAmount();
		}
	}
	totalAngry *= 50;
	return totalAngry+count;
}

void GameM::stu_getout() {
	getoutCount++;
	increaseFlipStudent();
}

inline void GameM::increaseFlipStudent() { 
	flipStudentCount++; 
	if (flipStudentCount >= 6) {
		gameover();
	}
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
