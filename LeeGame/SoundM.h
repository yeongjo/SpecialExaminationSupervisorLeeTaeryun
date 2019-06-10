#pragma once
#include <fmod.h>

class SoundM {
public:
	static FMOD_SYSTEM *g_System;  // FMOD system ���� ����

	static FMOD_SOUND **(sound [20]);


	static void init() {
		if (g_System) return;
		FMOD_System_Create(&g_System); // FMOD system ��ü ����
		FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL); // FMOD system �ʱ�ȭ

		for (size_t i = 0; i < 20; i++) {
			sound [i] = new FMOD_SOUND *;
			*sound [i] = nullptr;
		}
	}
	static void Release() {
		//FMOD_Sound_Release(sound); // FMOD sound ��ü ����
		FMOD_System_Close(g_System); // FMOD system ��ü clsoe
		FMOD_System_Release(g_System); // FMOD system ��ü ����
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
		//sterma(sound[0], "sound/�ڰ�� ȿ����.wav", true, .05f);
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
		sterma(sound [5], channel, "sound/å����� ������.mp3", false, .1f);
	}

	static void pop() {
		static FMOD_CHANNEL *channel;
		sterma(sound[0],channel, "sound/��ǳ��.mp3", false, .4f);
	}

	static FMOD_CHANNEL *sleepChannel;
	static int sleepCount;
	static void sleep() {
		sleepCount++;
		sterma(sound [1], sleepChannel, "sound/�ڰ�� ȿ����.wav", true, .1f);
	}
	static void stopSleep() {
		sleepCount--;
		if (sleepCount == 0)
			FMOD_Channel_Stop(sleepChannel);
	}

	static void TikTop() {
		static FMOD_CHANNEL *channel;
		sterma(sound [2], channel, "sound/�ð���ħ.wav", true, .1f);
		static FMOD_CHANNEL *channel2;
		sterma(sound [8], channel, "sound/BGM.mp3", true, .05f);
	}


	static void guyGetoutSound() {

	}

	// �����̼Ҹ�������
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

	// ���� ����ٳ���
	static void paperDrop() {

	}
	// �л� �巡���ϴ¼Ҹ� ����� ���Ǵ�
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

