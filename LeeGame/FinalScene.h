#pragma once
#include "MyMain.h"
class FinalScene :
	public Manager {
	vector<int> score;

	static CImage *img;
public:
	FinalScene();
	~FinalScene();

	void init();
	void tick();
	void render(HDC h);
};

