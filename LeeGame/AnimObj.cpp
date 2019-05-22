#include "AnimObj.h"



AnimSprite::AnimSprite() {
}


AnimSprite::~AnimSprite() {
}

void AnimSprite::init(Pos<> _splitUV) {
	splitUV = _splitUV;
	animDelayTimer = MTimer::create(100, true, false);
}

void AnimSprite::changeAnim(UINT i) {
	if (i == spriteGroupIdx) return;
	spriteGroupIdx = i % animIdxGroup.size();
	spriteSecondIdx = 0;
}

void AnimSprite::goNextSpriteIdx() {
	if (MTimer::isEnd(animDelayTimer) || animIdxGroup.size() == 0) return;
	// 다음애니메이션으로 전환
	spriteSecondIdx = (spriteSecondIdx + 1) % animIdxGroup[spriteGroupIdx].size();
	spriteIdx = animIdxGroup[spriteGroupIdx][spriteSecondIdx];
}

void AnimSprite::render(HDC h, Pos<float>& p, Pos<float> &size) {
	// TODO 애니메이션 가로세로 다 나눌건지 명확하게하기
	int sx = size.x, sy = size.y;
	int x = p.x, y = p.y;
	assert(animImgs.size() != 0);
	auto& tImage = animImgs [spriteGroupIdx];
	UINT nSpriteWidth = tImage->GetWidth() / splitUV.x;
	UINT nSpriteHeight = tImage->GetHeight() / splitUV.y;
	UINT xCoord = spriteIdx % splitUV.x;
	UINT yCoord = spriteIdx / splitUV.x;

	tImage->Draw(h, x, y, sx, sy,
		xCoord * nSpriteWidth, yCoord * nSpriteHeight,
		nSpriteWidth, nSpriteHeight);
}
