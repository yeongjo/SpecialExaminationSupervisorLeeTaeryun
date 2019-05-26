#include "Desk.h"
#include "Student.h"

Desk::Desk() {
}


Desk::~Desk() {
}

void Desk::init(Student *stu, int x, int y) {
	sitStudent = stu;
	sitStudent->sitDesk = this;
	sitStudent->p.set(x, y);
	p.set(x, y);
}

void Desk::flip() {
	// TODO 책상뒤집힌 애니메이션
}
