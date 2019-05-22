#include "ClickObj.h"
#include "GameInputM.h"


ClickObj::ClickObj() : Obj() {
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
