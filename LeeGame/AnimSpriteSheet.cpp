#include "AnimSpriteSheet.h"
#include "MTimer.h"

void AnimSpriteSheet::init(Pos<> _splitUV) {
	splitUV = _splitUV;
	animDelayTimer = MTimer::create(100, true, false);
}

void AnimSpriteSheet::changeAnim(UINT i) {
	if (i == spriteGroupIdx) return;
	spriteGroupIdx = i % animIdxGroup.size();
	spriteSecondIdx = 0;
	isAnimEnd = false;
}

void AnimSpriteSheet::goNextSpriteIdx() {
	if (MTimer::isEnd(animDelayTimer) || animIdxGroup.size() == 0 || isAnimEnd) return;
	// 다음애니메이션으로 전환
	int prevSpriteIdx = spriteIdx;
	spriteSecondIdx = (spriteSecondIdx + 1) % animIdxGroup[spriteGroupIdx].size();
	spriteIdx = animIdxGroup[spriteGroupIdx][spriteSecondIdx];
	if (spriteIdx == -1) {
		spriteIdx = prevSpriteIdx;
		isAnimEnd = true;
	}
}

void AnimSpriteSheet::render(HDC h, Pos<float>& p, Pos<float> &size) {
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