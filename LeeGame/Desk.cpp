#include "Desk.h"
#include "Student.h"
#include "AnimSpriteByImages.h"

Desk::Desk() {
	anim = new AnimSpriteByImages();
	// TODO å�� �ִϸ��̼� ��Ʈ ������ �����ϱ�
	vector<vector<wstring>> s;
	s.resize(3);
	s [0].push_back(L"img/desk_flip_0000.png");
	s [1].push_back(L"img/desk_flip_0001.png");
	s [2].push_back(L"img/desk_nopaper.png");
	anim->init(s);
}


Desk::~Desk() {
}

void Desk::init(Student *stu, int x, int y) {
	sitStudent = stu;
	sitStudent->sitDesk = this;
	sitStudent->p.set(x, y);
	sitStudent->size.set(44 * 2, 55 * 2);
	size.set(44 * 2, 55 * 2);
	p.set(x, y);
}

void Desk::flip() {
	// TODO å������� �ִϸ��̼�
	anim->changeAnim(1);
}

void Desk::render(HDC h) {
	auto _t = p + off;
	anim->render(h, _t, size);
}
