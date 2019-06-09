#pragma once
#include "Guy.h"
class AnimSpriteByImages;
class DanceGuy :
	public Guy {
	AnimSpriteByImages *sprite;
	static AnimSpriteByImages *preLoadSprite;
public:
	DanceGuy();
	~DanceGuy();

	static void loadImg();

	void tick();

	void render(HDC h);
};

