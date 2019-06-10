#include "AnimSpriteByImages.h"
#include <atlimage.h>

BLENDFUNCTION AnimSpriteByImages::blend = {AC_SRC_OVER, 0,255,AC_SRC_ALPHA};

void AnimSpriteByImages::init(vector<vector<wstring>> &imgNames, int delay) {
		imgs.resize(imgNames.size());
	for (size_t i = 0; i < imgNames.size(); i++) {
		for (size_t j = 0; j < imgNames[i].size(); j++) {
			auto t_image = new CImage();
			assert(!FAILED(t_image->Load(imgNames [i][j].c_str())));
			auto t = new FrameBlock(t_image, delay);
			imgs[i].push_back(t);
		}
	}
}

void AnimSpriteByImages::tick(int deltaTime) {
	int size = imgs [imgIdx].size();
	if(size == 1) return;

	imgs [imgIdx][subImgIdx];
	int time = imgs [imgIdx][subImgIdx]->update(deltaTime);
	if (time) {
		subImgIdx = (subImgIdx + 1) % size;
		FrameBlock *t = imgs [imgIdx][subImgIdx];
		
		if ((int)t == -1) { // 멈춤
			--subImgIdx;
		} else if ((int)t == -2) { // 다음애니메이션으로
			imgIdx = (int)imgs [imgIdx][subImgIdx + 1];
		}
	}
}

void AnimSpriteByImages::changeAnim(UINT i) {
	assert(i >= 0 && i < imgs.size());
	imgIdx = i;
	subImgIdx = 0;
}

void AnimSpriteByImages::render(HDC h, Pos<float> &p, Pos<float> &size) {
	// TODO 이어서 해야함
	int width = imgs [imgIdx][subImgIdx]->img->GetWidth();
	int height = imgs [imgIdx][subImgIdx]->img->GetHeight();
	imgs [imgIdx][subImgIdx]->img->AlphaBlend(h, p.x, p.y, size.x, size.y, 0, 0, width, height, 255,AC_SRC_OVER);
}
