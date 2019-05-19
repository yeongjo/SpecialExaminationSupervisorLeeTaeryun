#include "Student.h"
#include "Classroom.h"


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
		// ����ħ
		// å����� ������
		angryFlipDesk();
	}
}

void Student::tick() {
}

void Student::angryFlipDesk() {
}

void Student::onceDown() {
	int i = 0; // TODO �׽�Ʈ
}

void Student::stayDown() {
}

void Student::render(HDC h) {
	sprite.render(h, p, size);
}

void StudentState::action(Student *stu) {
	stu->getClassroom()->makeAngryStudentInClass(stu, amount, range);
	// TODO ���ϴ� �ִϸ��̼����� �ٲ���ϱ�
	stu->sprite.changeAnim(0);
}
