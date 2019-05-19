#include "Classroom.h"



Classroom::Classroom() {
}


Classroom::~Classroom() {
}

void Classroom::init(int idx) {
	//TODO layout
	size.set(500, 500);
	p.set((idx-1) * size.x, 100);

	constexpr int studentCount = 9;
	desks.resize(studentCount);
	students.resize(studentCount);

	vector<int> ran = unDuplicateRandom(studentCount, studentCount);

	Student::Type types [studentCount] = 
	{Student::Type::kind,(Student::Type)0,(Student::Type)0,
		(Student::Type)0,(Student::Type)0,(Student::Type)0,
		(Student::Type)0,(Student::Type)0,(Student::Type)0};

	StudentState *(states [studentCount]) = {
		new KindStudentState(),new StudentState(),new StudentState(),
		new StudentState(),new StudentState(),new StudentState(),
		new StudentState(),new StudentState(),new StudentState()
	};

	for (size_t i = 0; i < studentCount; i++) {
		desks [i] = new Desk();
		students [i] = new Student();

		// 중복없는 난수대로 초기화한다
		// Type, State
		students [i]->init(types[ran[i]],states[ran[i]]);

		// TODO layout 학생간격을 설정함
		int leftUpOff = 100;
		int xGap = 80, yGap = 80;
		int x = p.x +leftUpOff+ i % 3 * xGap, y = p.y+leftUpOff + i / 3 * yGap;
		desks [i]->init(students[i], x, y);
	}
}

void Classroom::makeAngryStudentInClass(Student *stu, float amount, float range) {
	for (size_t i = 0; i < students.size(); i++) {
		if(students [i] != stu && (students[i]->p-stu->p).squareLength() < range*range)
			students [i]->takeAngryDamage(amount);
	}
}

void Classroom::removeStudent(int i) {
	students.erase(students.begin() + i);
}

void Classroom::render(HDC h) {

}
