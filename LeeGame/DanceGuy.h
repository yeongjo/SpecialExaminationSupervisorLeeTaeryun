#pragma once
#include "Guy.h"
class AnimSpriteByImages;
class DanceGuy :
	public Guy {
	AnimSpriteByImages *sprite;
	static AnimSpriteByImages *preLoadSprite;
	Classroom *m_class = nullptr;
public:
	DanceGuy();
	~DanceGuy();

	static void loadImg();

	void tick();

	bool startDance(Classroom *_class);

	void render(HDC h);

	void giveDamage(Classroom *_class);

	bool isDestroyZone() {
		if (!m_class) return false;
		auto _class = m_class;
		RECT rt = {_class->p.x- 100, _class->p.y, _class->p.x+_class->size.x * .12f, _class->p.y+_class->size.y};
		bool _t = collPointRect(p.x, p.y, &rt);
			isAble = _t;
		return _t;
	}
};

