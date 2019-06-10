#include "Student.h"
#include "Classroom.h"
#include "GameM.h"

Student::Student() : Guy() {
}


Student::~Student() {
	myClass->removeStudent(this);
	if (spy)
		spy->targetStu = nullptr;
	if (popMsgObj)
		delete popMsgObj;
}

void Student::loadImages() {
	wstring t_names[] = {L"black", L"blue", L"red", L"yel"};
	for (size_t i = 0; i < 4; i++) {
		wstringstream ss;
		vector<vector<wstring>> s(7);
		ss << L"img/stu_" << t_names [i] << L"_flip_0000.png";
		s [0].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_angry.png";
		s[1].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_flip_0001.png";
		s[2].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_dance_0000.png";
		s[3].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_dance_0001.png";
		s[3].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_sleep.png";
		s[4].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_flip_0001.png";
		s[5].push_back(ss.str());ss.str(L"");
		ss << L"img/stu_" << t_names [i] << L"_wantchange.png";
		s[6].push_back(ss.str());ss.str(L"");
		preloadSprite [i] = new AnimSpriteByImages();
		preloadSprite [i]->init(s);
	}
}

void Student::init(Student::Type type, StudentState *state, Classroom *_class) {
	sprite = new AnimSpriteByImages(*preloadSprite[random(4)]);
	if (this->state)
		delete this->state;
	this->type = type;
	setState(state);
	myClass = _class;
}

void Student::setState(StudentState *_state) {
	if (!state) delete state;
	state = _state;
}

void Student::takeAngryDamage(float amount) {
	angryAmount += amount;
	angryAmount = angryAmount < 0 ? 0 : angryAmount;
	if (angryAmount >= 1) {
		// 개빡침
		// 책상엎고 나가기
		angryFlipDesk();
	}
}

void Student::resetState() {
	if (!state) return;
	state->fixState(this);
}

void Student::onceUpWithOutMouseCheck() {
	if (isDraging) {
		SoundM::studentDrop();
	}
	Guy::onceUpWithOutMouseCheck();
}

inline void Student::popMsg(int idx) {
	popMsgObj = UI::getIns().broadcastPopMsg(idx, p, this);
	SoundM::pop();
}

void Student::tick() {
	sprite->tick(deltatime);
	if (state != nullptr) state->fixState(this);

	if (isHisDeskFilped) {
		flipRemoveTimer -= deltatime;
		if (flipRemoveTimer < 0) {
			delete this;
		}
	}
}

void Student::action() {
	if (!state) return;
	state->action(this);	
//	SoundM::flipSound();
}

bool Student::activeState() {
	if (!state) return false;
	return state->active(this);
}

void Student::angryFlipDesk() {
	sitDesk->flip();
	if (state) {
		delete state;
		state = nullptr;
	}
	GameM::getIns().increaseFlipStudent();
	sprite->changeAnim(2);
	isHisDeskFilped = true;
	SoundM::flip();
}

void Student::annoySound() {
	// 고민하는 소리 , 말풍선
	SoundM::annoySound();
}

void Student::render(HDC h) {
	auto t = p + off;
	sprite->render(h, t, size);

	renderRect(h, t.x, t.y, angryUiSize, 5, RGB(20,20,20));
	angryAmount = angryAmount > 1 ? 1 : angryAmount;
	float _size = angryAmount * angryUiSize;
	renderRect(h, t.x, t.y, _size, 5, RGB(210,20,20));
}

bool Student::isDestroyZone() {
	auto _class = getClassroom();
	RECT rt = {_class->p.x- 100, _class->p.y, _class->p.x+_class->size.x * .12f, _class->p.y+_class->size.y};
	return collPointRect(p.x, p.y, &rt);
	//return false;
}

void Student::removePopMsg() {
	if(popMsgObj)
	popMsgObj->isDelete = true;
}

void StudentState::action(Student *stu) {
	if (!myState || !isAble) return;
	myState->action(stu);
}

bool StudentState::active(Student *stu) {
	if (myState) {
		if (myState->isAble) return false;
		myState->isAble = true;
	}
	if (myState) delete myState;
	myState = StudentStateMaker::makeNewState();
	myState->isAble = true;
	myState->_active(stu);
	return true;
 }

void SpyStudentState::action(Student *stu) {
	if (!isAble) return;
	stu->getSprite()->changeAnim(5);
	if(targetStu)
	targetStu->takeAngryDamage(amount);
}

void DropPaperStudentState::action(Student *stu) {
	if (!isAble) return;
	stu->getSprite()->changeAnim(1);
	stu->sitDesk->changeTestPaperState(2);
	stu->takeAngryDamage(amount);
}


void StudentState::fixState(Student *stu) {
	if (myState) {
		myState->fixState(stu);
		
	}else if (stu->getIsMouseDown()) {
		fix(stu);
	}
}

// 랜덤으로 각 교시에 맞는 상태 넘김
// 이어서 해야함
StudentState *StudentStateMaker::makeNewState() {
	float ran = random();
	int period = GameM::getIns().getPeriod();
	switch (period) {
	case 1:
		return new WantChangePaperStudentState();
		break;
	case 2:
		if (ran < .3f) {
			return new DropPaperStudentState();
		} else {
			return new WantChangePaperStudentState();
		}
		break;
	case 4:case 3:
		if (ran < .25f) {
			return new DropPaperStudentState();
		} else if (ran < .5f) {
			return new WantChangePaperStudentState();
		}else if (ran < .75f) {
			return new SleepStudentState();
		}else {
			return new DanceStudentState();
		}
		break;
	}
}
AnimSpriteByImages *Student::preloadSprite [4] = {0};

void WantChangePaperStudentState::action(Student *stu) {
	if (!isAble) return;
	stu->getSprite()->changeAnim(6);
	stu->takeAngryDamage(amount);
	SoundM::wantChangePaperSound();
}

void WantChangePaperStudentState::fixState(Student *stu) {
	RECT rt = {stu->p.x, stu->p.y, stu->p.x+stu->size.x, stu->p.y+stu->size.y};
	Pos<float> _paperPos = stu->getClassroom()->paper->lastDragDropPos + stu->getClassroom()->paper->size * .5f;
	if (collPointRect(_paperPos, &rt)) {
		fix(stu);
		stu->getClassroom()->paper->lastDragDropPos.y = -200;
	}
}

void SleepStudentState::action(Student *stu) {
	if (!isAble) return;
	stu->getSprite()->changeAnim(4);
	stu->getClassroom()->makeAngryStudentInClass(stu, amount, range);
	if (isPlaying) return;
	isPlaying = true;
	SoundM::sleep();
}

void DanceStudentState::action(Student *stu) {
	if (!isAble) return;
	stu->getSprite()->changeAnim(3);
	stu->getClassroom()->makeAngryStudentInClass(stu, amount, range);
}
