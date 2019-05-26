#include "MTimer.h"


vector<DelayC> MTimer::managingObjs;
vector<DelayC>::iterator MTimer::iter;
int MTimer::id;


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
