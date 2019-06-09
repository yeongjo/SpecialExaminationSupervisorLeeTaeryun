#include "ClickObj.h"
#include "GameInputM.h"


ClickObj::ClickObj(int layer) : Obj(layer) {
	GameInputM::getIns().addClickObj(this);
}


ClickObj::~ClickObj() {
	GameInputM::getIns().removeClickObj(this);
}

bool ClickObj::isMouseOver(int x, int y) {
	RECT rt = {p.x + off.x, p.y + off.y, 
		p.x + size.x + off.x, p.y + size.x + off.y};
	if (collPointRect(x, y, &rt)) {
		return true;
	}
	return false;
}

void ClickObj::onceDown() {
	isMouseDown = true;
}

void ClickObj::stayDown() {
	isMouseStay = true;
}

void ClickObj::onceUp() {
	isMouseDown = false;
	isMouseStay = false;
}