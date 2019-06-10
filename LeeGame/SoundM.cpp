#include "SoundM.h"

FMOD_SYSTEM *SoundM::g_System;
FMOD_SOUND** SoundM::sound[20];
FMOD_CHANNEL* SoundM::sleepChannel = nullptr;
int SoundM::sleepCount = 0;