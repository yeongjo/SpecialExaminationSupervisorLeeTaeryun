#include "Classroom.h"
#include "ClockObj.h"
#include "DanceGuy.h"

CImage *Classroom::img = nullptr;
ClockObj *clockObj = nullptr;
CImage *TestPaper::img = nullptr;

void loadClockImg() {
	if (clockObj) return;
	clockObj = new ClockObj(218 * 2, 80 * 2);
}

Classroom::Classroom() {
	loadClockImg();
}


Classroom::~Classroom() {
}

void Classroom::init(int idx) {
	isInit = true;
	if (img == nullptr) {
		img = new CImage();
		auto _t = !FAILED(img->Load(L"img/class.jpg"));
		assert(_t);
		Student::loadImages();

		for (size_t i = 0; i < 3; i++) {
			numImg [i] = new CImage();
			wstringstream ss;
			ss << L"img/"<< i+1 << L" Class.png";
			numImg [i]->Load(ss.str().c_str());
		}
		
	}
	if(!danceGuy)
		danceGuy = new DanceGuy();
	danceGuy->isAble = false;
	classIdx = idx;
	size.set(classroomX, classroomY);
	p.set((idx-1) * size.x, 0);
	off.x = 0;


	constexpr int studentCount = 9;
	for (size_t i = 0; i < desks.size(); i++)
		delete desks [i];
	for (size_t i = 0; i < students.size(); i++)
		delete students [i];
	desks.clear();
	desks.resize(studentCount);
	students.clear();
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
		students [i]->init(types[ran[i]],states[ran[i]], this);

		int leftOff = 134*2;
		int upOff = 163*2;
		int xGap = 71*2, yGap = 52*2;
		int x = p.x +leftOff+ i % 3 * xGap, y = p.y+upOff + i / 3 * yGap;
		desks [i]->init(students[i], x, y);
	}
	if(!paper)
		paper = new TestPaper(p);

	isInit = false;
}

void Classroom::makeAngryStudentInClass(Student *stu, float amount, float range) {
	for (size_t i = 0; i < students.size(); i++) {
		if(students [i] != stu && (students[i]->p-stu->p).squareLength() < range*range)
			students [i]->takeAngryDamage(amount);
	}
}

//void Classroom::makeAngryThisStuent(Student *stu, float amount) {
//	stu->takeAngryDamage(amount);
//}

void Classroom::removeStudent(int i) {
	if (isInit) return;
	delete students [i];
	students.erase(students.begin() + i);
}

void Classroom::removeStudent(Student *stu) {
	if (isInit) return;
	for (size_t i = 0; i < students.size(); i++) {
		if (students [i] == stu) {
			students.erase(students.begin() + i);
			
			return;
		}
	}
}

void Classroom::changeOffX(float _x) {
	off.x += _x;
	for (size_t i = 0; i < students.size(); i++) {
		students [i]->off.x = off.x;
	}
	for (size_t i = 0; i < desks.size(); i++) {
		desks [i]->off.x = off.x;
	}
	paper->off.x = off.x;
	danceGuy->off.x = off.x;
}

inline bool Classroom::startDance() {
	return danceGuy->startDance(this);
}

inline void Classroom::giveDanceDamage() {
	danceGuy->giveDamage(this);
}

void Classroom::tick() {
}

void Classroom::render(HDC h) {
	img->StretchBlt(h, p.x+off.x, p.y+off.y, size.x, size.y, SRCCOPY);
	numImg [classIdx]->Draw(h, p.x+off.x, p.y+off.y);
	clockObj->render(h, p.x+off.x, p.y+off.y); 
}

size_t Classroom::getStudentSize() {
	return students.size();
}

CImage *Classroom::numImg[3];