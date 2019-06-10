#pragma once
#include <fmod.h>

class SoundM{
public:
		static FMOD_SYSTEM *g_System;  // FMOD system ���� ����

		static FMOD_SOUND **(sound[20]);


	static void init() {
		if (g_System) return;
		FMOD_System_Create(&g_System); // FMOD system ��ü ����
		FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL); // FMOD system �ʱ�ȭ

		for (size_t i = 0; i < 20; i++)
		{
			sound[i] = new FMOD_SOUND*;
			*sound[i] = nullptr;
		}
	}
	static void Release() {
		//FMOD_Sound_Release(sound); // FMOD sound ��ü ����
		FMOD_System_Close(g_System); // FMOD system ��ü clsoe
		FMOD_System_Release(g_System); // FMOD system ��ü ����
	}
	static void update() {
		FMOD_System_Update( g_System );
	}
	static void annoySound() {
		//FMOD_DEFAULT
		//FMOD_LOOP_NORMAL
		//sterma(sound[0], "sound/�ڰ�� ȿ����.wav", true, .05f);
	}
	static void flip() {
		sterma(sound[0], "sound/å����� ������.mp3", false, .1f);
	}

	static void pop() {
		//sterma(sound[0], "sound/��ǳ��.mp3", false, 1.f);
	}

	static FMOD_CHANNEL* sleepChannel;
	static int sleepCount;
	static void sleep() {
		sleepCount++;
		sleepChannel = sterma(sound[1], "sound/�ڰ�� ȿ����.wav", true, .1f);
	}
	static void stopSleep() {
		sleepCount--;
		if(sleepCount == 0)
			FMOD_Channel_Stop(sleepChannel);
	}

	static void TikTop() {
		sterma(sound[2], "sound/�ð���ħ.wav", true, .1f);
	}

	
	static void guyGetoutSound() {

	}
	// �����̼Ҹ�������
	static void wantChangePaperSound() {
		sterma(sound[3], "sound/ahh sound effec.mp3", false, 0.1f);
	}

	static FMOD_CHANNEL* headDanceChannel;
	static int headDanceCount;
	static void headDance() {

	}
	static void stopHeadDance() {

	}
	// ���� ����ٳ���
	static void paperDrop() {

	}
	// �л� �巡���ϴ¼Ҹ� ����� ���Ǵ�
	static void studentDrop() {

	}

private:
	static FMOD_CHANNEL* sterma(FMOD_SOUND** sound, const char* ch, bool isLoop, float volume) {
		
		UINT mode = isLoop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;
		static FMOD_CHANNEL* channel;
		if (!*sound) {
			FMOD_System_CreateSound(
				g_System,
				ch,
				mode,
				0,
				sound
			);
		}
		if(channel)
			FMOD_Channel_Stop(channel);
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, *sound, 0, &channel);
		FMOD_Channel_SetVolume(channel, volume);
		//FMOD_Sound_Release(*sound);
		return channel;
	}
};

