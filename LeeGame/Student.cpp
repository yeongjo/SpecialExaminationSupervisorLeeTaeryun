#include "Student.h"
#include "Classroom.h"
#include "GameM.h"

Student::Student() : Guy() {
}


Student::~Student() {
}

void Student::loadImages() {
	wstring t_names[] = {L"black", L"blue", L"red", L"yel"};
	for (size_t i = 0; i < sizeof(t_names); i++) {
		wstringstream ss;
		// TODO 학생 이미지 갯수정하는부분 컨닝때문에 추가될예정
		vector<vector<wstring>> s(5);
		ss << L"img/stu_" << t_names [i] << L"_flip_0000.png";
		s [0].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_angry.png";
		s[1].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_flip0001.png";
		s[2].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_dance_0000.png";
		s[3].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_dance_0001.png";
		s[3].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_sleep.png";
		s[4].push_back(ss.str());ss.str(L"");
		preloadSprite [i] = new AnimSpriteByImages();
		preloadSprite [i]->init(s);
	}
}

void Student::init(Student::Type type, StudentState *state) {
	sprite = preloadSprite[random(4)];
	this->type = type;
	setState(state);
}

void Student::setState(StudentState *_state) {
	if (!state) delete state;
	state = _state;
}

void Student::takeAngryDamage(float amount) {
	angryAmount += amount;
	if (angryAmount > 1) {
		// 개빡침
		// 책상엎고 나가기
		angryFlipDesk();
	}
}

void Student::resetState() {

}

void Student::tick() {
	sprite->tick(deltatime);
}

void Student::angryFlipDesk() {
	sitDesk->flip();
}

void Student::annoySound() {
	// 고민하는 소리 , 만ㄹ풍선
	SoundM::annoySound();
}

void Student::render(HDC h) {
	sprite->render(h, p, size);
}

void StudentState::action(Student *stu) {
	if(isAble) myState->action(stu);
}

void SpyStudentState::action(Student *stu) {
	targetStu->takeAngryDamage(amount);
}

void DropPaperStudentState::action(Student *stu) {
	if (!isAble) return;
	stu->takeAngryDamage(amount);
	// TODO 원하는 애니메이션으로 바뀌게하기
	stu->getSprite()->changeAnim(0);
}


void DropPaperStudentState::fixState(Student *stu) {
	if (stu->getIsMouseDown()) {
		isAble = false;
	}
}

// 랜덤으로 각 교시에 맞는 상태 넘김

inline StudentState *StudentStateMaker::makeNewState(int _period) {
	float ran = random();
	int period = GameM::getIns().getPeriod();
	switch (_period) {
	case 1:
		return new DropPaperStudentState();
		break;
	case 2:
		if (ran < .3f) {
			return new DropPaperStudentState();
		} else if (ran < .6f) {
			return new DropPaperStudentState();
		}
		break;
	case 3:
		break;
	case 4:
		break;
	}
}
