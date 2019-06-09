#include "Student.h"
#include "Classroom.h"
#include "GameM.h"

Student::Student() : Guy() {
}


Student::~Student() {
}

void Student::init(Student::Type type, StudentState *state) {
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
}

void Student::angryFlipDesk() {
	sitDesk->flip();
}

void Student::annoySound() {
	// 고민하는 소리 , 말풍선
}

void Student::render(HDC h) {
	//TODO 이미지로 바꿔주기
	Guy::render(h);
	return;
	sprite.render(h, p, size);
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
