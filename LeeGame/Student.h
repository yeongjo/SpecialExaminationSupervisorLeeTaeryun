#pragma once
#include "AnimObj.h"

class StudentState; class Classroom;

// Classroom, GameM에서 vector로 가지고있음

// 얼마나 민폐끼치는친구인지 태어날때 정해짐
// 한명은 스파이가 있다.
// 이상징후 발생 타이밍은 GameM에서 쏴주고 이상징후 발생만 학생이함
class Student : public Guy {
	friend class Desk;
	friend class StudentState;
public:
	enum class Type;
private:
	// 위치 참조할때도 필요
	Desk *sitDesk; // 엎어버릴때 필요

	Classroom *myClass; // 교실에 피해끼칠때필요

	AnimSprite sprite; // TODO 초기화해야함 사진 불러오고 set UV

	Type type; // GameM가 init 함수를 통해 설정해줌

	StudentState *state;

	//	[송영조] [18:11] int로 1부터 100까지 범위하면
	//	[송영조] [18:11] 제일 작은게 1로 증가시키는거라 애매하니까
	//	[송영조] [18:12] 그냥 float [0 ~ 1] 까지로 해둠 엔간한거

	// [0 ~ 1] 가짐
	float angryAmount;
public:
	Student();
	~Student();

	// 학생 타입이랑, 상태설정해주기
	void init(Student::Type type, StudentState *state);

	void setState(StudentState *state);

	// Classroom 에게서 받음
	// 근처에서 날 화나게 하는 사람이 있으면 수치증가
	void takeAngryDamage(float amount);

	// 화남수치 오름
	virtual void tick();

	void angryFlipDesk();

	// 고민하는 소리
	void annoySound();

	virtual void onceDown();
	virtual void stayDown();

	virtual void render(HDC h);


	Classroom *getClassroom() { return myClass; }

	enum class Type {
		normal, //  ㅄ
		spy, // 더 ㅄ 한명밖에 없음 
		kind // 아무잘못도안함 답안지교체정도
	};
};

// 고민 메모
// 우짤까 상태 지정하고 그 상태맞게만 행동하게할까
// 그냥 플레이어 안에서 switch로 다 할까
// 전자로 할려
//
// 스스로 자기에게 피해주는 행동
//	시험지 떨굼,  교체, 
// 남들에게 피해주는 행동
//	머리흔들기, 코골이, 옆사람꺼 컨닝하기
//	컨닝하기는 *Student 받아와서 확장하기
class StudentState {
	// 영향끼칠 범위랑 양
	float range, amount;
public:
	// 다른사람 혹은 나에게 무슨 영향을 주는지
	// 나의 애니메이션이 어떤거로 바뀌는지 여기서 결정
	virtual void action(Student *stu);
};

// 특수 상태
class KindStudentState :public StudentState{
	virtual void action(Student *stu) {}
};

class SpyStudentState : public StudentState {
	virtual void action(Student *stu); // TODO 애니메이션 인덱스를 몰라서 추가못함
};

class StudentStateMaker {
public:
	static StudentState *makeNewState(int i) {
		switch (i) {
		case 0:

			break;
		}
	}
};