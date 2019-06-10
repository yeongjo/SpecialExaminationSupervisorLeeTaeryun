#include "DanceGuy.h"
#include "AnimSpriteByImages.h"
#include "Classroom.h"

AnimSpriteByImages *DanceGuy::preLoadSprite = nullptr;
inline DanceGuy::DanceGuy() {
	loadImg();
	size.set(44 * 2, 59 * 2);
	sprite = new AnimSpriteByImages(*preLoadSprite);
}

inline DanceGuy::~DanceGuy() {
	delete sprite;
}

inline void DanceGuy::loadImg() {
	if (preLoadSprite) return;
	preLoadSprite = new AnimSpriteByImages();
	wstringstream ss;
	vector<vector<wstring>> s(1);
	for (size_t i = 0; i < 8; i++) {
		ss << L"img/dance_000" << i << L".png";
		s [0].push_back(ss.str());
		ss.str(L"");
		//ss.clear();
	}
	preLoadSprite->init(s, 37);
}

inline void DanceGuy::tick() {
	if (!isAble) return;
	sprite->tick(deltatime);
}

inline bool DanceGuy::startDance(Classroom *_class) {
	if (isAble) return false;
	m_class = _class;
	p.set(90*2+_class->p.x, 300*2+_class->p.y);
	SoundM::dance();
	return isAble = true;
}

inline void DanceGuy::render(HDC h) {
	if (!isAble) return;
	auto t = p + off;
	sprite->render(h, t, size);
}

inline void DanceGuy::giveDamage(Classroom *_class) {
	if (!isAble) return;
	int _size = _class->getStudentSize();
	for (size_t i = 0; i < _size; i++) {
		_class->getStudent(i)->takeAngryDamage(0.1f);
	}
}
