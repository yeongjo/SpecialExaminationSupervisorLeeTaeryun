#pragma once
#include <fmod.h>
class SoundM{
public:
		static FMOD_SYSTEM *g_System;  // FMOD system 변수 선언
	static void init() {
		if (g_System) return;
		FMOD_System_Create(&g_System); // FMOD system 객체 생성
		FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL); // FMOD system 초기화
	}
	static void Release() {
		//FMOD_Sound_Release(sound); // FMOD sound 객체 해제
		FMOD_System_Close(g_System); // FMOD system 객체 clsoe
		FMOD_System_Release(g_System); // FMOD system 객체 해제
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
				"sound/책상엎고 나가기.mp3",
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

