#pragma once

class DelayC {
	int remainTime;
	int _remainTime = 0;
	bool isLoop;
	bool isBreak = false;
	
public:
	int idx = 0;

	DelayC(int _remain, bool _isLoop, bool beginStart, int id);

	// isLoop�� false�� return isBreak ������ ������ �˾Ƽ� �����
	bool tick(int add = 1);

	void setEnd();

	void setRemainTime(int _remain, bool _isLoop);

	void changeRemainTime(int time);

	bool isEnd();

	void debugRemainTime(HDC hdc, int x, int y);

	void reset();

	// ������ ������ ������ �������� �������
	void endNext();
};

// Ÿ�̸� ���ÿ��� �������� Timer�� ���ֱ�
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

	// ������ ������ ������ �������� �������
	static void endNext(int idx);

	static bool isHere(int idx);

	static void debug(HDC hdc, int x, int y);
};