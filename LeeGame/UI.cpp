#include "UI.h"
#include "Student.h"


UI::UI() {
}


UI::~UI() {
}

void UI::broadcastMain(wstring msg) {

}

void UI::broadcastRound(int round) {
	//new RoundBroadcastObj(round);
}

GameoverBroadcastObj * UI::broadcastGameover() {
	DBOUT(L"gameover\n");
	return new GameoverBroadcastObj();
}
PopMsgBroadcastObj *UI::broadcastPopMsg(int idx, Pos<float>& _p, Student *stu) {
	DBOUT(idx<<L" : PopMsg\n");
	return new PopMsgBroadcastObj(idx, _p,stu);
}
CImage *RoundBroadcastObj::roundImg [3] = {0};
CImage *BroadcastObj::img = nullptr;
CImage *PopMsgBroadcastObj::roundImg [10] = {0};

inline PopMsgBroadcastObj::~PopMsgBroadcastObj() {
	_stu->popMsgObj = nullptr;
}
