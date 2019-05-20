#include "MyMain.h"

vector<DelayC> MTimer::managingObjs;
vector<DelayC>::iterator MTimer::iter;
int MTimer::id;

RECT rectView;

int deltatime = 15;

WindowM win;

vector<SceneM> SceneM::self;

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

// 원기준으로 사각형방향 반환
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

//template<typename T>
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


void SceneM::reset() {
		for (size_t i = 0; i < objs.size(); i++) {
			for (size_t j = 0; j < objs [i].size(); j++) {
				delete objs [i][j];
			}
			objs [i].clear();
		}
	}

void SceneM::render(HDC hdc) {
	size_t s1 = objs.size();
	for (size_t i = 0; i < s1; i++) {
		size_t s2 = objs [i].size();
		for (size_t j = 0; j < s2; j++) {
			objs[i][j]->render(hdc);
		}
	}
}

class MovableObj :public Obj {
public:
	MovableObj(int layer):Obj(layer){}
	virtual ~MovableObj() {}
	float speed = 3;
	virtual void move () {

	}
	virtual void render (HDC hdc) {
	}
};

void SceneM::tick() {
	size_t s1 = objs.size();
	for (size_t i = 0; i < s1; i++) {
		size_t s2 = objs [i].size();
		for (size_t j = 0; j < s2; j++) {
			objs [i][j]->tick();
		}
	}
}

void SceneM::destoryObj(Manager *obj) {
	Manager *t;
	size_t s1 = objs.size();
	for (size_t i = 0; i < s1; i++) {
		size_t s2 = objs [i].size();
		for (size_t j = 0; j < s2; j++) {
			t = objs [i][j];
			if (t == obj) {
				// 스스로 delete 됬을때만 이곳으로 오기때문에 delete 안해도됨
				//delete t;
				objs[i].erase(objs[i].begin() + j);
				return;
			}
		}
	}
}

 Pos<> ads(Pos<>a) {
	int x = a.x >= 0 ? a.x : -a.x;
	int y = a.y >= 0 ? a.y : -a.y;
	return Pos<>(x, y);
}