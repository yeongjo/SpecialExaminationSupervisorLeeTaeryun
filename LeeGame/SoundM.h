#pragma once
#include <fmod.h>

class SoundM {
public:
	static FMOD_SYSTEM *g_System;  // FMOD system 변수 선언

	static FMOD_SOUND **(sound [20]);


	static void init() {
		if (g_System) return;
		FMOD_System_Create(&g_System); // FMOD system 객체 생성
		FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL); // FMOD system 초기화

		for (size_t i = 0; i < 20; i++) {
			sound [i] = new FMOD_SOUND *;
			*sound [i] = nullptr;
		}
	}
	static void Release() {
		//FMOD_Sound_Release(sound); // FMOD sound 객체 해제
		FMOD_System_Close(g_System); // FMOD system 객체 clsoe
		FMOD_System_Release(g_System); // FMOD system 객체 해제
	}
	static void update() {
		FMOD_System_Update(g_System);
	}

	static void reset() {
		headDanceCount = sleepCount = 1;
		stopSleep();
		stopHeadDance();
	}

	static void annoySound() {
		//FMOD_DEFAULT
		//FMOD_LOOP_NORMAL
		//sterma(sound[0], "sound/코고는 효과음.wav", true, .05f);
	}


	static FMOD_CHANNEL *danceChannel;
	static int danceCount;
	static void dance() {
		danceCount++;
		if(danceCount == 1)
		sterma(sound [7], danceChannel, "sound/dance.mp3", false, .13f);
	}
	static void stopDance() {
		danceCount--;
		if (danceCount == 0)
			FMOD_Channel_Stop(danceChannel);
	}


	static void flip() {
		static FMOD_CHANNEL *channel;
		sterma(sound [5], channel, "sound/책상엎고 나가기.mp3", false, .1f);
	}

	static void pop() {
		static FMOD_CHANNEL *channel;
		sterma(sound[0],channel, "sound/말풍선.mp3", false, .4f);
	}

	static FMOD_CHANNEL *sleepChannel;
	static int sleepCount;
	static void sleep() {
		sleepCount++;
		sterma(sound [1], sleepChannel, "sound/코고는 효과음.wav", true, .1f);
	}
	static void stopSleep() {
		sleepCount--;
		if (sleepCount == 0)
			FMOD_Channel_Stop(sleepChannel);
	}

	static void TikTop() {
		static FMOD_CHANNEL *channel;
		sterma(sound [2], channel, "sound/시계초침.wav", true, .1f);
		static FMOD_CHANNEL *channel2;
		sterma(sound [8], channel, "sound/BGM.mp3", true, .05f);
	}


	static void guyGetoutSound() {

	}

	// 잉잉이소리같은거
	static void wantChangePaperSound() {
		static FMOD_CHANNEL *channel;
		sterma(sound [3], channel, "sound/Duck Toy Long.mp3", false, 0.1f);
	}

	static FMOD_CHANNEL *headDanceChannel;
	static int headDanceCount;
	static void headDance() {
		headDanceCount++;
		sterma(sound [4], headDanceChannel, "sound/Duck Toy Long.mp3", false, 0.1f);
	}
	static void stopHeadDance() {
		headDanceCount--;
		if (headDanceCount == 0)
			FMOD_Channel_Stop(headDanceChannel);
	}

	// 종이 들었다놨다
	static void paperDrop() {

	}
	// 학생 드래그하는소리 들었다 내렷다
	static void studentDrop() {
		static FMOD_CHANNEL *channel;
		sterma(sound [6], channel, "sound/Duck Toy.mp3", false, 0.1f);
	}

private:
	static FMOD_CHANNEL *sterma(FMOD_SOUND **sound, FMOD_CHANNEL *&channel, const char *ch, bool isLoop, float volume) {

		UINT mode = isLoop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;
		if (!*sound) {
			FMOD_System_CreateSound(
				g_System,
				ch,
				mode,
				0,
				sound
			);
		}
		if (channel)
			FMOD_Channel_Stop(channel);
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, *sound, 0, &channel);
		FMOD_Channel_SetVolume(channel, volume);
		//FMOD_Sound_Release(*sound);
		return channel;
	}
};

