#pragma once

#include "Student.h"
using namespace std;

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
public:
	Classroom();
	~Classroom();

	// TODO 교실의 좌표랑 책상들 배치를 어떻게 하지

	/* TODO 이미지 불러오기
	 학생 수 9명으로 초기화
	 교실의 사이즈 설정
	 i에 따라 위치가 x방향으로 교실 사이즈만큼 밀려나게하기
	 */
	// 학생과 책상을 모두 초기화함
	void init(int i);

	// 다른사람들을 화나게하고싶을때 호출
	void makeAngryStudentInClass(Student *stu, float amount, float range);

	void removeStudent(int i);

	// TODO 이미지 그리기
	virtual void render(HDC h);

	size_t getStudentSize();
	//자동으로 assert 되니까 안함
	Student *getStudent(int i) { return students [i]; }
};

