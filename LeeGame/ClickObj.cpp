#include "ClickObj.h"
#include "GameInputM.h"


ClickObj::ClickObj() : Obj() {
	GameInputM::s.addClickObj(this);
}


ClickObj::~ClickObj() {
	GameInputM::s.removeClickObj(this);
}

bool ClickObj::isMouseOver(int x, int y) {
	RECT rt = {p.x + off.x, p.y + off.y, size.x + off.x, size.x + off.y};
	if (collPointRect(x, y, &rt)) {
		return true;
	}
	return false;
}
