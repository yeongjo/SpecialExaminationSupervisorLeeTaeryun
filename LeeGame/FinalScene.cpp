#include "FinalScene.h"

CImage *FinalScene::img = nullptr;
FinalScene::FinalScene() {
	if (img == nullptr) {
		img = new CImage();
		img->Load(L"img/best.jpg");
	}
}

FinalScene::~FinalScene() {
	// 저장
	DBOUT(L"hi\n");;;;;;;
}

void FinalScene::init() {

	// 파일에서 불러올
	//score.push_back(30);
	//score.push_back(12);
	//score.push_back(1);
	//

	score.push_back(GameM::getIns().calculateClearScore());

	sort(score.begin(), score.end(), greater<int>());

	score.resize(3);
}

void FinalScene::tick() {
	auto rbuttonup = KeyM::GetInst()->OnceKeyUp(VK_RBUTTON);
	if (rbuttonup) {
		GameM::getIns().goMainScene();
	}
}

void FinalScene::render(HDC h) {
	img->Draw(h, 0, 0);
	// 218, 300
	// 0,36
	int x = 218, y = 300;
	wstringstream ss;

	
	for (size_t i = 0; i < 3; i++) {
		ss << score[i];
		TextOut(h, x, y, ss.str().c_str(), ss.str().size()); ss.str(L"");
		ss.clear();
		y += 34;
	}
	
}
