#include "GameInputM.h"
#include "ClickObj.h"


GameInputM::GameInputM() {
	KeyM::GetInst();
}


GameInputM::~GameInputM() {
}

void GameInputM::init(HWND hWnd) {
	this->hWnd = hWnd;
}

void GameInputM::removeClickObj(ClickObj *obj) {
		size_t size = clickObjs.size();
		for (size_t i = 0; i < size; i++) {
			if (clickObjs [i] == obj) {
				clickObjs.erase(clickObjs.begin() + i);
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
	auto keyInst = KeyM::GetInst();
	bool bOnceDown = keyInst->OnceKeyDown(VK_LBUTTON);
	bool bStayDown = keyInst->StayKeyDown(VK_LBUTTON);
	bool bOnceUp = keyInst->OnceKeyUp(VK_LBUTTON);
	size_t size = clickObjs.size();
	if (bOnceDown || bStayDown || bOnceUp) {
		for (size_t i = 0; i < size; i++) {
			if (clickObjs [i]->isMouseOver(x, y)) {
				if (bOnceDown) clickObjs [i]->onceDown();
				if (bStayDown) clickObjs [i]->stayDown();
				if (bOnceUp) clickObjs [i]->onceUp();
			}
			if (bStayDown) clickObjs [i]->drag();
		}
	}
	
}

GameInputM GameInputM::s;