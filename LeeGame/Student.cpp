#include "Student.h"
#include "Classroom.h"
#include "GameM.h"

Student::Student() : Guy() {
}


Student::~Student() {
}

void Student::init(Student::Type type, StudentState *state) {
	setState(state);
}

void Student::setState(StudentState *_state) {
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

void Student::onceDown() {
	int i = 0;
}

void Student::stayDown() {
}

void Student::render(HDC h) {
	//TODO 이미지로 바꿔주기
	Guy::render(h);
	return;
	sprite.render(h, p, size);
}

void StudentState::action(Student *stu) {
	stu->getClassroom()->makeAngryStudentInClass(stu, amount, range);
	// TODO 원하는 애니메이션으로 바뀌게하기
	stu->sprite.changeAnim(0);
}

void SpyStudentState::action(Student *stu) {
}
