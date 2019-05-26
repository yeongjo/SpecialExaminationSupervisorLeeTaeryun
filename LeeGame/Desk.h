#pragma once
#include "Guy.h"
class Student;
class Desk : public Obj{

	// TODO 책상엔 시험지가 있고 떨어지면 줍거나 교체할수있음
	class TestPaper {
	public:
		bool isDrop; // 떨어트림
		bool isMess; // 잘못적어서 교체해달라할거임
	};
	TestPaper testPaper;

	Student *sitStudent; // 앉아있는 학생 일어날수도 있음
	// 학생도 Desk 참조해서 엎기
public:
	Desk();
	~Desk();

	// GameM으로 부터 학생 받기
	// 학생에 sitDesk에 자기를 줌
	// 위치 지정도 해야할듯
	void init(Student *stu, int x, int y);

	void flip();

	Student *getStudent() { return sitStudent; }
};

