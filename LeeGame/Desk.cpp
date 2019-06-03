#include "Desk.h"
#include "Student.h"
#include "AnimObj.h"

Desk::Desk() {
	anim = new AnimSprite();
	// TODO 책상 애니메이션 시트 들어오면 수정하기
	anim->init(Pos<>(1,1));


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
	anim->changeAnim(1);
}
