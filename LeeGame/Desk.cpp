#include "Desk.h"
#include "Student.h"
#include "AnimObj.h"

Desk::Desk() {
	anim = new AnimSprite();
	// TODO å�� �ִϸ��̼� ��Ʈ ������ �����ϱ�
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
	// TODO å������� �ִϸ��̼�
	anim->changeAnim(1);
}
