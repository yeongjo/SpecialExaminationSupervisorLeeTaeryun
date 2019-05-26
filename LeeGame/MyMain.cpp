#include "MyMain.h"

// Use this (return timer ID)
// 타이머 사용시에는 마지막에 Timer라 해주기

inline int MTimer::create(int _remainTime, bool _isLoop, bool beginStart) {
	managingObjs.push_back(DelayC(_remainTime, _isLoop, beginStart, id));
	return id++;
}

// input ID and use

inline int MTimer::create(int _remainTime, int _id, bool _isLoop, bool beginStart) {
	if (id < _id) return 0;
	managingObjs.push_back(DelayC(_remainTime, _isLoop, beginStart, _id));
	id = _id + 1;
	return 1;
}

// must call this on other tick

inline void MTimer::tick(int add) {
	int t = 0;
	for (iter = managingObjs.begin(); iter != managingObjs.end(); ++t) {
		if (iter->tick(add)) {
			iter = managingObjs.erase(iter);
		} else
			++iter;
	}
}

inline bool MTimer::isEnd(int idx) {
	for (size_t i = 0; i < managingObjs.size(); i++) {
		if (managingObjs [i].idx == idx) {
			return managingObjs [i].isEnd();
		}
	}
	return false;
}

inline void MTimer::setEnd(int idx) {
	for (size_t i = 0; i < managingObjs.size(); i++) {
		if (managingObjs [i].idx == idx) {
			return managingObjs [i].setEnd();
		}
	}
}

inline void MTimer::changeEndTime(int idx, int time) {
	for (size_t i = 0; i < managingObjs.size(); i++) {
		if (managingObjs [i].idx == idx) {
			return managingObjs [i].changeRemainTime(time);
		}
	}
}

// 처음부터 다시시작할수있게함

inline void MTimer::reset(int idx) {
	for (size_t i = 0; i < managingObjs.size(); i++) {
		if (managingObjs [i].idx == idx) {
			return managingObjs [i].reset();
		}
	}
}

// 다음에 무조건 끝나는 조건으로 만들어줌

inline void MTimer::endNext(int idx) {
	for (size_t i = 0; i < managingObjs.size(); i++) {
		if (managingObjs [i].idx == idx) {
			return managingObjs [i].endNext();
		}
	}
}

inline bool MTimer::isHere(int idx) {
	for (size_t i = 0; i < managingObjs.size(); i++) {
		if (managingObjs [i].idx == idx) {
			return true;
		}
	}
	return false;
}

inline void MTimer::debug(HDC hdc, int x, int y) {
	int textY = 0;
	for (size_t i = 0; i < managingObjs.size(); i++) {
		managingObjs [i].debugRemainTime(hdc, x, y + textY);
		textY += 15;
	}
}

// call when window size change

inline void WindowM::init(HWND hwnd) {
	RECT rt;
	GetClientRect(hwnd, &rt);
	init(hwnd, rt.right, rt.bottom);
}

inline void WindowM::init(HWND hwnd, int _x, int _y) {
	size.set(_x, _y);
	initRandom(); // 꼽사리
	this->hwnd = hwnd;
}

inline HDC WindowM::prerender(HDC hdc) {
	if (!hbit)
		hbit = CreateCompatibleBitmap(hdc, size.x, size.y);
	mainDc = hdc;
	if (!dc)
		dc = CreateCompatibleDC(hdc);
	oldBit = (HBITMAP)SelectObject(dc, hbit);

	renderRect(dc, 0, 0, size.x, size.y, bkColor);
	return dc;
}

inline void WindowM::postrender() {
	BitBlt(mainDc, 0, 0, size.x, size.y, dc, 0, 0, SRCCOPY);
	SelectObject(dc, oldBit);
	//ReleaseDC(hwnd, dc);
}

inline void WindowM::postrender(int x, int y) {
	BitBlt(mainDc, x, y, size.x, size.y, dc, 0, 0, SRCCOPY);
	SelectObject(dc, oldBit);
	//ReleaseDC(hwnd, dc);
}

// call in tick() plz;

inline void WindowM::clearWindow() {
	InvalidateRect(hwnd, NULL, false);
}

inline const Pos<> &WindowM::getSize() const {
	return size;
}
