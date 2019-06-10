#pragma once
#include "AnimSpriteByImages.h"

class StudentState; class Classroom; class PopMsgBroadcastObj;

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
	

	Classroom *myClass; // 교실에 피해끼칠때필요

	// 0 : 평범 문제푸는거 손까닥까닥, 가만히 있는거 추가할지 고민
	// 1 : 가만히 있는거
	// 2 : 머리흔드는거

	static AnimSpriteByImages* preloadSprite[4];
	AnimSpriteByImages *sprite;

	Type type; // GameM가 init 함수를 통해 설정해줌

	StudentState *state = nullptr;

	//	[송영조] [18:11] int로 1부터 100까지 범위하면
	//	[송영조] [18:11] 제일 작은게 1로 증가시키는거라 애매하니까
	//	[송영조] [18:12] 그냥 float [0 ~ 1] 까지로 해둠 엔간한거

	// [0 ~ 1] 가짐
	float angryAmount;
	float angryUiSize = 85;

	bool isHisDeskFilped = false;
	int flipRemoveTimer = 1000;

public:
	// 위치 참조할때도 필요
	Desk *sitDesk; // 엎어버릴때 필요
	PopMsgBroadcastObj *popMsgObj = nullptr;

	Student();
	~Student();

	static void loadImages();

	// 학생 타입이랑, 상태설정해주기
	void init(Student::Type type, StudentState *state, Classroom *_class);

	void setState(StudentState *state);

	// Classroom 에게서 받음
	// 근처에서 날 화나게 하는 사람이 있으면 수치증가
	void takeAngryDamage(float amount);

	// TODO 이상징후 초기화
	void resetState();

	// 화남수치 오름
	virtual void tick();

	// 주변에 지속적인 피해주기
	void action();

	// 활성화해서 주변에 피해주게하기
	// 이미활성화되있으면 false 반환
	bool activeState();

	void angryFlipDesk();

	// 고민하는 소리, 말풍선
	void annoySound();

	virtual void render(HDC h);

	bool isDestroyZone();

	void removePopMsg();

	void onceDown() {
		Guy::onceDown();
		SoundM::studentDrop();
	}
	void onceUpWithOutMouseCheck();

	void popMsg(int idx);
	
	Classroom *getClassroom() { return myClass; }
	AnimSpriteByImages *getSprite() { return sprite; }

	float getAngryAmount() { return angryAmount; }

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

/* 매번 교체하고 실행하는식으로 할까
그러면 착한친구가 덮어씌워질수도 있음 */
class StudentState {
protected:
	// 현재상태
	//StudentStateMaker 로 GameM에서 상태만들어줌
	StudentState *myState;
	// 영향끼칠 범위랑 양
	float range, amount;
	// 데미지 줄때만 활성화, 해결하면 비활성화
	bool isAble = false;
	// 소리가 재생되는지 한번만 재생할거라서 씀
	bool isPlaying = false;
public:
	// 다른사람 혹은 나에게 무슨 영향을 주는지
	// 나의 애니메이션이 어떤거로 바뀌는지 여기서 결정
	// 이 안에서 랜덤으로 이 중 하나가 나오게 한다.
	// stu는 이 함수를 실행한 친구를 줌
	virtual void action(Student *stu);

	// 활성화 이미활성화되있으면 false 리턴
	virtual bool active(Student *stu);

	virtual bool _active(Student *stu) { return true; }

	// 상태해결조건이 맞으면 상태해결
	// 학생에서 클릭인지 드래그중인지 상태를 가져온다.
	virtual void fixState(Student *stu);

	void alwaysFixState(Student *stu){
		isAble = false;
		isPlaying = false;
		stu->getSprite()->changeAnim(0);
	}


protected:
	virtual void fix(Student *stu) {
		alwaysFixState(stu);
	}
};

// 시험지 교체해달라하는 상태
// 시험지 떨구는 상태
// 코고는 상태
// 머리흔들기
// 코골이

class DropPaperStudentState : public StudentState {
public:
	DropPaperStudentState() { range = 0; amount = 0.05f; }
	bool _active(Student *stu) {
		SoundM::wantChangePaperSound();
		stu->popMsg(2);
		return true;
	}
	virtual void action(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		stu->sitDesk->changeTestPaperState(0);
		stu->removePopMsg();
	}
};

class WantChangePaperStudentState : public StudentState {
public:
	WantChangePaperStudentState() { range = 0; amount = 0.05f; }
	bool _active(Student *stu) {
		SoundM::wantChangePaperSound();
		stu->popMsg(1);
		return true;
	}
	virtual void action(Student *stu);
	virtual void fixState(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		stu->removePopMsg();
	}
};

class SleepStudentState : public StudentState {
public:
	SleepStudentState() { range = 300; amount = 0.02f; }
	bool _active(Student *stu) {
		stu->popMsg(0);
		return true;
	}
	virtual void action(Student *stu);
	//void fixState(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		SoundM::stopSleep();
		stu->removePopMsg();
	}
};

class DanceStudentState : public StudentState {
public:
	DanceStudentState() { range = 300; amount = 0.02f; }
	bool _active(Student *stu) {
		SoundM::headDance();
		return true;
	}
	virtual void action(Student *stu);
	//void fixState(Student *stu);
	virtual void fix(Student *stu) {
		StudentState::fix(stu);
		SoundM::stopHeadDance();
	}
};

// 특수 상태
class KindStudentState :public StudentState{
	virtual void action(Student *stu) {}
	virtual bool active(Student *stu) { return true; }
};

// 컨닝하기
class SpyStudentState : public StudentState {
	Student *targetStu;
public:
	SpyStudentState(Student *_targetStu) : targetStu(_targetStu){range = 0; amount = 0.1f;}
	virtual bool active(Student *stu) {
		bool _t = isAble;
		isAble = true;
		return !_t;
	}
	virtual void action(Student *stu);
};

class StudentStateMaker {
public:
	// 랜덤으로 각 교시에 맞는 상태 넘김
	static StudentState *makeNewState();
};