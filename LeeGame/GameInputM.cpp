#include "GameInputM.h"
#include "ClickObj.h"
#include "KeyM.h"


GameInputM::GameInputM() {
	KeyM::GetInst();
}


GameInputM::~GameInputM() {
}

void GameInputM::init(HWND hWnd,Pos<> *dbStartPos) {
	this->hWnd = hWnd;
	this->dbStartPos = dbStartPos;
}

void GameInputM::removeClickObj(ClickObj *obj) {
		size_t size = clickObjs.size();
		for (size_t i = 0; i < size; i++) {
			if (clickObjs [i] == obj) {
				clickObjs.erase(clickObjs.begin() + i);
				--size;
			}
		}
}

void GameInputM::setMousePos() {
	GetCursorPos(&mousePos);
	assert(hWnd);
	ScreenToClient(hWnd, &mousePos);
}

void GameInputM::tick() {
	setMousePos();
	int x = mousePos.x, y = mousePos.y;
	if (!dbStartPos) return;
	x -= dbStartPos->x;
	y -= dbStartPos->y;
	auto keyInst = KeyM::GetInst();
	bool bOnceDown = keyInst->OnceKeyDown(VK_LBUTTON);
	bool bStayDown = keyInst->StayKeyDown(VK_LBUTTON);
	bool bOnceUp = keyInst->OnceKeyUp(VK_LBUTTON);
	int size = (int)clickObjs.size();
	if (bOnceDown || bStayDown || bOnceUp) {
		for (int i = size-1; i >= 0; i--) {
			if (clickObjs [i]->isMouseOver(x, y)) {
				if (bOnceDown) clickObjs [i]->onceDown();
				if (bStayDown) clickObjs [i]->stayDown();
				if (bOnceUp) clickObjs [i]->onceUp();
			}
			if (bStayDown) clickObjs [i]->drag();
		}
	}
	
}

GameInputM *GameInputM::s = nullptr;