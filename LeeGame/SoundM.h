#pragma once
#include <fmod.h>
class SoundM{
public:
		static FMOD_SYSTEM *g_System;  // FMOD system ���� ����
	static void init() {
		if (g_System) return;
		FMOD_System_Create(&g_System); // FMOD system ��ü ����
		FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL); // FMOD system �ʱ�ȭ
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
		static FMOD_SOUND *sound;
		static FMOD_CHANNEL *channel;
		if (!sound) {
			FMOD_System_CreateSound(
				g_System,
				"sound/å����� ������.mp3",
				FMOD_LOOP_NORMAL,
				0,
				&sound
			);
		}
		FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, sound, 0, &channel);
		FMOD_Channel_SetVolume(channel, .01f);
	}
	static void destroySound() {

	}
	static void flip() {

	}

};

