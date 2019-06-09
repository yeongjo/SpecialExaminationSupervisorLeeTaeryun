#pragma once

#include "Student.h"
using namespace std;

constexpr int classroomX = 464*2;
constexpr int classroomY = 426*2;

class TestPaper;

// 교실

// GameM에서 가지고있음

// 학생은 9명이 기본

//나가는문좌표를가지고있고
//교실안에 있는 학생들을 관리한다.
// 필요하면 이 교실에서 문제학생 발생됬다고 알려주는거도 가능할듯

// 글로벌 민폐를 할때도 여기서 함
// 글로벌 민폐시 그 친구가 특정 함수를 불러 본인을 제외한
// 다른 모든 학생들에게 피해를 줌
class Classroom : public Obj{
	// 학생을 상속받는 사이코가 있을거라 포인터로 함
	vector<Student*> students;
	vector<Desk *> desks;
	static CImage *img;

	bool isInit = false;
public:
	TestPaper *paper = nullptr;
	
	Classroom();
	~Classroom();

	/* TODO 이미지 불러오기
	 학생 수 9명으로 초기화
	 교실의 사이즈 설정
	 i에 따라 위치가 x방향으로 교실 사이즈만큼 밀려나게하기
	 */
	// 학생과 책상을 모두 초기화함
	void init(int i);

	// 다른사람들을 화나게하고싶을때 호출
	// stu에는 이 사람을 제외한 사람이 화나게 한다. 보통은 본인으로
	void makeAngryStudentInClass(Student *stu, float amount, float range);
	//void makeAngryThisStuent(Student *stu, float amount);

	void removeStudent(int i);
	void removeStudent(Student *stu);

	void changeOffX(float _x);

	void tick();

	// TODO 이미지 그리기
	virtual void render(HDC h);

	size_t getStudentSize();
	//자동으로 assert 되니까 안함
	Student *getStudent(int i) { return students [i]; }
};

class TestPaper : public Guy{
public:
	Pos<float> lastDragDropPos;
	static CImage *img;

	static void loadImg() {
		if (img) return;
		img = new CImage();
		img->Load(L"img/testpaper.jpg");
	}

	TestPaper(Pos<float>& _p){
		p = _p+Pos<float>(221*2,328*2);
		loadImg();
		size.x = img->GetWidth()<<1;
		size.y = img->GetHeight()<<1;
	}
	void render(HDC h) {
		if (!isAble) return;
		auto t = p + off;
		img->StretchBlt(h, t.x, t.y, size.x, size.y, SRCCOPY);
	}

	void onceUp() {
		if (isDraging) {
			lastDragDropPos = p;
		}
		Guy::onceUp();
	}
	void onceDown() {
		Guy::onceDown();
		SoundM::paperDrop();
	}
	void onceUpWithOutMouseCheck() {
		if (isDraging) {
		SoundM::paperDrop();
	}
	Guy::onceUpWithOutMouseCheck();
	}

	bool isDestroyZone() { return false; }
};