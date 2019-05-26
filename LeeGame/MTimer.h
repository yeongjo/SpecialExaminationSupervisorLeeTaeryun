#pragma once

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

// 타이머 사용시에는 마지막에 Timer라 해주기
class MTimer {
	static vector<DelayC> managingObjs;
	static vector<DelayC>::iterator iter;
	static int id;
public:
	static int create(int _remainTime, bool _isLoop = false, bool beginStart = true);

	// input ID and use
	static int create(int _remainTime, int _id, bool _isLoop = false, bool beginStart = true);

	// must call this on other tick
	static void tick(int add = 1);

	static bool isEnd(int idx);

	static void setEnd(int idx);

	static void changeEndTime(int idx, int time);

	static void reset(int idx);

	// 다음에 무조건 끝나는 조건으로 만들어줌
	static void endNext(int idx);

	static bool isHere(int idx);

	static void debug(HDC hdc, int x, int y);
};