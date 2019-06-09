#include "DanceGuy.h"
#include "AnimSpriteByImages.h"
AnimSpriteByImages *DanceGuy::preLoadSprite = nullptr;
inline DanceGuy::DanceGuy() {

}

inline DanceGuy::~DanceGuy() {
	delete sprite;
}

inline void DanceGuy::loadImg() {
	if(preLoadSprite)
	preLoadSprite = new AnimSpriteByImages();
	wstringstream ss;
	vector<vector<wstring>> s(1);
	//ss << L"img/stu_" << t_names [i] << L"_flip_0000.png";
	//preLoadSprite->init(s);
}

inline void DanceGuy::tick() {

}

inline void DanceGuy::render(HDC h) {
	auto t = p + off;
	sprite->render(h, t, size);
}
