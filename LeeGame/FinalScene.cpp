#include "FinalScene.h"


CImage *FinalScene::img = nullptr;
FinalScene::FinalScene() {
	if (img == nullptr) {
		img = new CImage();
		img->Load(L"img/best.jpg");
	}
}

FinalScene::~FinalScene() {
	// ÀúÀå
	DBOUT(L"hi\n");;;;;;;
}

void FinalScene::init() {
	char FileName[100] = "Pizza.txt";
	FILE* fptr = NULL;
	score.resize(3);
	if (!fopen_s(&fptr, FileName, "r+")) {
		while (!feof(fptr))
		{
			for (size_t i = 0; i < 3; i++)
			{
				fscanf_s(fptr, "%d ", &score[i]);
			}
		}
		fclose(fptr);
	}

	score.push_back(GameM::getIns().calculateClearScore());

	sort(score.begin(), score.end(), greater<int>());

	score.resize(3);

	if (!fopen_s(&fptr, "Pizza.txt", "wt")) {
		for (size_t i = 0; i < 3; i++)
		{
			fprintf(fptr, "%d ", score[i]);
		}
		fclose(fptr);
	}
	SoundM::Final();
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
	int x = 218, y = 295;
	wstringstream ss;

	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
	VARIABLE_PITCH | FF_ROMAN, TEXT("³ª´®°íµñ"));
	HFONT OldFont = (HFONT)SelectObject(h, hFont);
	SetTextColor(h, RGB(233, 233, 233));

	SetBkMode(h, TRANSPARENT);
	for (size_t i = 0; i < 3; i++) {
		ss << score[i];
		TextOut(h, x, y, ss.str().c_str(), ss.str().size()); ss.str(L"");
		ss.clear();
		y += 34;
	}
	
	SelectObject(h, OldFont);
	DeleteObject(hFont);
}
