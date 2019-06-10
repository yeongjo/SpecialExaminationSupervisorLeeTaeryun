#pragma once
#include "MyMain.h"
class FinalScene :
	public Manager {
public:
	FinalScene();
	~FinalScene();

	void tick();
	void render(HDC h);
};

