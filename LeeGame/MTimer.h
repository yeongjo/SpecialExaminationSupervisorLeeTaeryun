#pragma once

// Ÿ�̸� ���ÿ��� �������� Timer�� ���ֱ�
class MTimer {
	static vector<DelayC> managingObjs;
	static vector<DelayC>::iterator iter;
	static int id;
public:
	// Use this (return timer ID)
	// Ÿ�̸� ���ÿ��� �������� Timer�� ���ֱ�
	static int create(int _remainTime, bool _isLoop = false, bool beginStart = true);

	// input ID and use
	static int create(int _remainTime, int _id, bool _isLoop = false, bool beginStart = true);

	// must call this on other tick
	static void tick(int add = 1);

	static bool isEnd(int idx);

	static void setEnd(int idx);

	static void changeEndTime(int idx, int time);

	// ó������ �ٽý����Ҽ��ְ���
	static void reset(int idx);

	// ������ ������ ������ �������� �������
	static void endNext(int idx);

	static bool isHere(int idx);

	static void debug(HDC hdc, int x, int y);
};