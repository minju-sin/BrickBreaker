#pragma once

#pragma comment(lib,"winmm.lib") 
#include <mmsystem.h>
#include <Digitalv.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openEnd;
MCI_PLAY_PARMS playEnd;
MCI_OPEN_PARMS openClear;
MCI_PLAY_PARMS playClear;

#define BGM "gamesound.wav"

int dwID;
void playingBgm()
{
    openBgm.lpstrElementName = TEXT(BGM);
    openBgm.lpstrDeviceType = TEXT("waveaudio");
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
    dwID = openBgm.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
}

void playSound(int track) {
    switch (track)
    {
    case 0:
        playingBgm();
        break;
    }
}