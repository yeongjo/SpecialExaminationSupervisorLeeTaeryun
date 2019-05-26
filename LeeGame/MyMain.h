#pragma once

#include "resource.h"

#include <windowsx.h>
#include <sstream>
#include <vector>
#include <time.h>
#include <math.h>
#include <atlimage.h>
#include <algorithm>
#include <fstream>
#include <memory>
#include <cassert>
#include <Commdlg.h>

#include "KeyM.h"

using namespace std;

#define PI 3.1415926535f
#define Radian PI/180

RECT rectView;
void getWindowSize(HWND hwnd);

template<typename T>
T ads(T a) {
	return a >= 0 ? a : -a;
}

void renderEllipse(HDC hdc, int _x, int _y, int _sizeX, int _sizeY, COLORREF color = RGB(255, 255, 0));
void renderCircle(HDC hdc, int _x, int _y, int _size = 10, COLORREF color = RGB(255, 255, 0));
void renderRoundRect(HDC hdc, int x, int y, int sizeX, int sizeY, int w, int h, COLORREF color);
void renderRect(HDC hdc, int _x, int _y, int _sizeX = 10, int _sizeY = 10, COLORREF color = RGB(255, 255, 0));
void renderTriangle(HDC hdc, int x, int y, int size, COLORREF color = RGB(255, 255, 0));

bool IsPointInCircle(int x, int y, int r, int px, int py);
bool collPointRect(int x, int y, RECT *rt);

template<typename TT=int>
struct Pos{
public:
	TT x = 0, y = 0;

	Pos() {}
	Pos(TT x, TT y) :x(x), y(y) {}

	void set(TT _x, TT _y) { x = _x; y = _y; }

	Pos<TT>operator- (const Pos<TT>& a) {
		Pos<TT>p;
		p.x = x - a.x;
		p.y = y - a.y;
		return p;
	}
	Pos<TT>operator- () {
		Pos<TT>p;
		p.x = -x;
		p.y = -y;
		return p;
	}
	Pos<TT>operator+ (const Pos<TT>& a) {
		Pos<TT>p;
		p.x = x + a.x;
		p.y = y + a.y;
		return p;
	}
	template<typename T>
	Pos<TT>& operator+= (const T& a) {
		x += a;
		y += a;
		return *this;
	}
	template<typename T>
	Pos<TT>& operator+= (const Pos<T>& a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	template<>
	Pos<TT> &operator+= (const Pos<float> &a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	template<typename T>
	Pos<TT> &operator+= (const Pos<TT> &a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	template<typename T>
	Pos<TT> &operator*= (const T &a) {
		x *= a;
		y *= a;
		return *this;
	}
	template<typename T>
	Pos<TT>& operator*= (const Pos<T>& a) {
		x *= a.x;
		y *= a.y;
		return *this;
	}
	template<>
	Pos<TT> &operator*= (const Pos<float> &a) {
		x *= a.x;
		y *= a.y;
		return *this;
	}
	Pos<TT>& operator/= (const Pos<TT>& a) {
		x /= a.x;
		y /= a.y;
		return *this;
	}
	template<typename T>
	Pos<TT>& operator/= (T a) {
		x /= a;
		y /= a;
		return *this;
	}
	template<typename T>
	Pos<TT>operator/ (T a) {
		Pos<TT>p;
		p.x = x / a;
		p.y = y / a;
		return p;
	}
	template<typename T>
	Pos<TT>operator* (T a) {
		Pos<TT>p;
		p.x = x * a;
		p.y = y * a;
		return p;
	}
	Pos<TT>& operator-= (const Pos<TT>& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
	bool operator==(const Pos<TT>& a) {
		float epsilon = 0.001f;
		if (::ads(x - a.x) <= epsilon && ::ads(y - a.y) <= epsilon)
			return true;
		return false;
	}

	bool operator!=(const Pos<TT>& a) {
		if (x != a.x || y != a.y)
			return true;
		return false;
	}
	template<typename T>
	bool operator<(T a) {
		if (x < a && y < a)
			return true;
		return false;
	}
	template<typename T>
	bool operator<=(T a) {
		if (x <= a && y <= a)
			return true;
		return false;
	}
	template<typename T>
	bool operator>(T a) {
		if (x > a && y > a)
			return true;
		return false;
	}
	template<typename T>
	bool operator>=(T a) {
		if (x >= a && y >= a)
			return true;
		return false;
	}

	bool isZero() {
		return x == 0 && y == 0;
	}

	Pos<TT> normalize() {
		
		return *this / length();
	}

	Pos<TT>ads() {
		return Pos<TT>(::ads(x), ::ads(y));
	}

	Pos<TT>onlyX() {
		return Pos<TT>(x, 0);
	}

	Pos<TT>onlyY() {
		return Pos<TT>(0, y);
	}

	Pos<TT>flipX() {
		return Pos<TT>(-x, y);
	}
	Pos<TT>flipY() {
		return Pos<TT>(x, -y);
	}

	TT squareLength() {
		return x *x + y * y;
	}

	float length() {
		return sqrtf(squareLength());
	}

	Pos<TT> rotate(float angle) {
		float co = cos(angle * PI / 180);
		float si = sin(angle * PI / 180);
		float _x = co *x - si * y;
		float _y = si * x + co * y;
		return Pos<TT>(_x, _y);
	}

	void setZero() { set(0, 0); }
};

// 원기준으로 사각형방향 반환
Pos<> CollCircleRect(int x, int y, int r, RECT *rt);

int normalize(int a);
void setAlign(Pos<> &a, Pos<> &b);
void initRandom();
// 0.0 ~ 1.0
float random();
// 0.0 ~ a
float random(float a);
// a 와 b 사이의 값 줌
int random(int a, int b);
int random(int a);
Pos<float> randomCircle(float size = 1);



class DelayC {
	int remainTime;
	int _remainTime = 0;
	bool isLoop;
	bool isBreak = false;
	
public:
	int idx = 0;

	DelayC(int _remain, bool _isLoop, bool beginStart, int id);

	// isLoop가 false면 return isBreak 루프가 끝나면 알아서 사라짐
	bool tick(int add = 1);

	void setEnd();

	void setRemainTime(int _remain, bool _isLoop);

	void changeRemainTime(int time);

	bool isEnd();

	void debugRemainTime(HDC hdc, int x, int y);

	void reset();

	// 다음에 무조건 끝나는 조건으로 만들어줌
	void endNext();
};


// 윈도사이즈
// 더블버퍼링
class WindowM {
	Pos<>size; // 윈도 사이즈
	HWND hwnd;

	HDC dc;
	HDC mainDc;

	HBITMAP hbit;
	HBITMAP oldBit;

	COLORREF bkColor = RGB(255,255,255);
public:
	// call when window size change
	void init(HWND hwnd);

	void init(HWND hwnd, int _x, int _y);

	HDC prerender(HDC hdc);

	void postrender();

	void postrender(int x, int y);

	// call in tick() plz;
	void clearWindow();

	const Pos<> &getSize() const;
};

#define BYE
#ifdef BYE

extern int deltatime;

class Manager;

// TODO 임시로 SceneM 메인에선 렌더 안했다가 게임시작시에만 
class SceneM {
	friend Manager;

	vector<vector<Manager*>> objs;
	static vector<SceneM> self;

	SceneM() {
		/*
		교실
		책상, 휴지통, 시계
		시험지, 
		사람들
		*/
		resizeLayer(4);
	}



	/*
	교실
	책상, 휴지통, 시계
	시험지, 
	사람들
	*/
	void addObj (Manager* obj, size_t layer) {
		assert(objs.size() > layer);
		objs[layer].push_back (obj);
	}
	
public:
	static SceneM &getIns(size_t i) { 
		if (i < 0 || i >= self.size()) assert("SceneM 에 있지도 않은 인덱스를 참조함"==0);
		return self [i]; 
	}
	void tick ();
	void render(HDC hdc);
	void destoryObj(Manager *obj);

	void reset();

	// TODO 줄일때 기존에것들 안지우고 줄임 나중에 추가하기
	void resizeLayer(int layerCount) {
		objs.resize(layerCount);
	}
};

WindowM win;

// 씬매니저에서 

class Manager {
public:
	Manager(int layer = 0) {
		addToM(layer);
	}
	virtual ~Manager() {
		SceneM::getIns(0).destoryObj(this);
	}
	void addToM(int layer) {
		SceneM::getIns(0).addObj (this, layer);
	}
	virtual void tick () {}
	virtual void render(HDC hdc){}
};

class Obj : Manager{
public:
	// Position
	Pos<float> p;
	// use for camera or shake
	Pos<float> off;

	Pos<float> size;
	COLORREF color = RGB(20, 20, 20);

	bool isAble = true;

	// 숫자가 커질수록 더 나중에 그려진다.
	Obj (int layer = 0) : Manager(layer){
	}
	
	virtual ~Obj() {}
	virtual void tick () {}
	virtual void render(HDC hdc){
		renderRect(hdc, static_cast<int>(p.x), static_cast<int>(p.y), (int)size.x, (int)size.y, RGB(20, 20, 20));
	}
	virtual int collObj(Obj *o) {
		if (o == nullptr) return 0;
		// 나갔을경우
		if ((p.x > o->p.x + o->size.x || p.x + size.x < o->p.x) ||
			(p.y > o->p.y + o->size.y || p.y + size.y < o->p.y))
			return 0;
		return 1;
	}
};

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

template<class T>
vector<T> unDuplicateRandom(int count, T range) {
	vector<T> t(count * 2);
	for (size_t i = 0; i < count; ) {
		t [i] = rand() % range;
		if (t [i + count] == 0) {
			t [i + count] = 1;
			i++;
		}
	}
	t.resize(count);
	return t;
}

#endif