#include "MyMain.h"

template<>
Pos<> ads(Pos<>a) {
	int x = a.x >= 0 ? a.x : -a.x;
	int y = a.y >= 0 ? a.y : -a.y;
	return Pos<>(x, y);
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

void getWindowSize(HWND hwnd) {
	GetClientRect(hwnd, &rectView);
}

void renderEllipse(HDC hdc, int _x, int _y, int _sizeX, int _sizeY, COLORREF color) {
	// 블럭사이즈대로 적용하기
	int x = _x;
	int y = _y;
	//int width = _width*.5f;

	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, x, y, x + _sizeX, y + _sizeY);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void renderCircle(HDC hdc, int _x, int _y, int _size, COLORREF color) {
	renderEllipse(hdc, _x, _y, _size, _size, color);
}

void renderRoundRect(HDC hdc, int x, int y, int sizeX, int sizeY, int w, int h, COLORREF color) {
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RoundRect(hdc, x, y, x + sizeX, y + sizeY, w, h);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void renderRect(HDC hdc, int _x, int _y, int _sizeX, int _sizeY, COLORREF color) {
	int x = _x, y = _y;
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, x, y, x + _sizeX, y + _sizeY);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void renderTriangle(HDC hdc, int x, int y, int size, COLORREF color) {
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x + size / 2, y + size / 2);
	LineTo(hdc, x, y);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

bool IsPointInCircle(int x, int y, int r, int px, int py) {
	int dx = x - px;
	int dy = y - py;
	int l = dx * dx + dy * dy;
	if (l > r * r)
		return false;
	return true;
}

bool collPointRect(int x, int y, RECT *rt) {
	if ((rt->left <= x && x <= rt->right) &&
		(rt->top <= y && y <= rt->bottom))
		return true;
	return false;
}


Pos<> CollCircleRect(int x, int y, int r, RECT *rt) {
	if ((rt->left <= x && x <= rt->right) ||
		(rt->top <= y && y <= rt->bottom)) {
		RECT rcEx = {
			rt->left - r,
			rt->top - r,
			rt->right + r,
			rt->bottom + r
		};

		if (rcEx.left < x && x < rcEx.right && rcEx.top < y && y < rcEx.bottom) {
			if (rt->left > x) return Pos<>(1, 0);
			if (x > rt->right) return Pos<>(-1, 0);
			if (rt->top > y) return Pos<>(0, 1);
			if (y > rt->bottom) return Pos<>(0, -1);
		}
	} else {
		if (IsPointInCircle(x, y, r, rt->left, rt->top))return Pos<>(1, 1);
		if (IsPointInCircle(x, y, r, rt->left, rt->bottom))return Pos<>(1, -1);
		if (IsPointInCircle(x, y, r, rt->right, rt->top))return Pos<>(-1, 1);
		if (IsPointInCircle(x, y, r, rt->right, rt->bottom))return Pos<>(-1, -1);
	}
	return Pos<>(0, 0);
}

int normalize(int a) {
	return a / ads<int>(a);
}

void setAlign(Pos<> &a, Pos<> &b) {
	int x = a.x, y = a.y;
	int x2 = b.x, y2 = b.y;
	b.x = max(x, x2);
	a.x = min(x, x2);
	b.y = max(y, y2);
	a.y = min(y, y2);
}

void initRandom() {
	srand(time(NULL));
}

// 0.0 ~ 1.0
float random() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

// 0.0 ~ a
float random(float a) {
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / a));
}

// a 와 b 사이의 값 줌
int random(int a, int b) {
	return rand() % (b - a) + a;
}

int random(int a) {
	return rand() % a;
}

Pos<float> randomCircle(float size) {
	return Pos<float>(random(size), random(size));
}

inline DelayC::DelayC(int _remain, bool _isLoop, bool beginStart, int id) {
	setRemainTime(_remain, _isLoop);
	idx = id;
	if (beginStart)
		_remainTime = remainTime + 1;
}

// isLoop가 false면 return isBreak 루프가 끝나면 알아서 사라짐

inline bool DelayC::tick(int add) {
	_remainTime += add;
	return isBreak;
}

inline void DelayC::setEnd() {
	isBreak = true;
}

inline void DelayC::setRemainTime(int _remain, bool _isLoop) {
	remainTime = _remain;
	isLoop = _isLoop;
}

inline void DelayC::changeRemainTime(int time) {
	remainTime = time;
}

inline bool DelayC::isEnd() {
	if (remainTime < _remainTime) {
		if (isLoop)
			_remainTime = 0;
		else
			isBreak = true;
		return true;
	}
	return false;
}

inline void DelayC::debugRemainTime(HDC hdc, int x, int y) {
#ifdef _MBCS
	stringstream ss;
#endif
#ifdef _UNICODE
	wstringstream ss;
#endif
	ss << idx << _T(":") << _remainTime << _T("/") << remainTime;
	TextOut(hdc, x, y, ss.str().c_str(), ss.str().size());
}

inline void DelayC::reset() {
	_remainTime = 0;
}

// 다음에 무조건 끝나는 조건으로 만들어줌

inline void DelayC::endNext() {
	_remainTime = remainTime + 1;
}
