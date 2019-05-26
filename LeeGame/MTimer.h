#pragma once

// 타이머 사용시에는 마지막에 Timer라 해주기
class MTimer {
	static vector<DelayC> managingObjs;
	static vector<DelayC>::iterator iter;
	static int id;
public:
	// Use this (return timer ID)
	// 타이머 사용시에는 마지막에 Timer라 해주기
	static int create(int _remainTime, bool _isLoop = false, bool beginStart = true);

	// input ID and use
	static int create(int _remainTime, int _id, bool _isLoop = false, bool beginStart = true);

	// must call this on other tick
	static void tick(int add = 1);

	static bool isEnd(int idx);

	static void setEnd(int idx);

	static void changeEndTime(int idx, int time);

	// 처음부터 다시시작할수있게함
	static void reset(int idx);

	// 다음에 무조건 끝나는 조건으로 만들어줌
	static void endNext(int idx);

	static bool isHere(int idx);

	static void debug(HDC hdc, int x, int y);
};