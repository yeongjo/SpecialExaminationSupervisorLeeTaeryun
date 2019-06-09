#include "UI.h"



UI::UI() {
}


UI::~UI() {
}

void UI::broadcastMain(wstring msg) {

}

void UI::broadcastRound(int round) {
	new BroadcastObj(round);
}
