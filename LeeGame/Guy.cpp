#include "Guy.h"
#include <limits>

constexpr float float_infi = numeric_limits<float>::infinity();

Guy::Guy(int layer) : ClickObj(layer) {
	prevDragPos.x = float_infi;
}


Guy::~Guy() {
}

void Guy::onceDown() {
	remainDragStayTime = 0;
	isMouseDown = true;
}

void Guy::stayDown() {
	isMouseStay = true;
	remainDragStayTime += deltatime;
	if (remainDragStayTime > 0 && isMouseDown) {
		isDraging = true;
		if(prevDragPos.x == float_infi)
			prevDragPos = p;
	}
}

void Guy::onceUp() {
	
}

void Guy::drag() {
	if (!isDraging)return;
	
	auto t = GameInputM::getIns().getMousePos();
	p.set(t.x - size.x/2 - off.x, t.y - size.y/2 - off.y);
}

inline void Guy::onceUpWithOutMouseCheck() {
	isMouseDown = false;
	isMouseStay = false;
	if (isDraging) { // 드래그 놓음
		if (isDestroyZone()) {
			SoundM::destroySound();
			delete this;
			return;
		}
		p = prevDragPos;
		prevDragPos.x = float_infi;
	}
	isDraging = false;
	remainDragStayTime = 0;
}
