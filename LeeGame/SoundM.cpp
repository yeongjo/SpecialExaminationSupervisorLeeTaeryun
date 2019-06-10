#include "SoundM.h"

FMOD_SYSTEM *SoundM::g_System;
FMOD_SOUND** SoundM::sound[20];
FMOD_CHANNEL* SoundM::sleepChannel = nullptr;
int SoundM::sleepCount = 0;
FMOD_CHANNEL* SoundM::headDanceChannel = nullptr;
int SoundM::headDanceCount = 0;