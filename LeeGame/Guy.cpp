#include "Guy.h"



Guy::Guy() : ClickObj() {
}


Guy::~Guy() {
}

void Guy::onceDown() {
	remainDragStayTime = 0;
}

void Guy::stayDown() {
	remainDragStayTime += deltatime;
	if (remainDragStayTime > 100) {
		isDraging = true;
	}
}

void Guy::onceUp() {
	isDraging = false;
	remainDragStayTime = 0;
}

void Guy::drag() {
	if (!isDraging)return;
	auto t = GameInputM::getIns().getMousePos();
	p.set(t.x - size.x/2, t.y - size.y/2);
}
