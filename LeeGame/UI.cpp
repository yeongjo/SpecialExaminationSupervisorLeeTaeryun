#include "UI.h"



UI::UI() {
}


UI::~UI() {
}

void UI::broadcastMain(wstring msg) {

}

void UI::broadcastRound(int round) {
	//new RoundBroadcastObj(round);
}

void UI::broadcastGameover() {
	DBOUT(L"gameover\n");
	return;
	new GameoverBroadcastObj();
}
PopMsgBroadcastObj *UI::broadcastPopMsg(int idx, Pos<float>& _p) {
	DBOUT(L"PopMsg\n");
	return new PopMsgBroadcastObj(idx, _p);
}
CImage *RoundBroadcastObj::roundImg [3] = {0};
CImage *BroadcastObj::img = nullptr;
CImage *PopMsgBroadcastObj::roundImg [10] = {0};