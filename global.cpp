#ifndef _global_cpp
#define _global_cpp
#include <windows.h>
#include "id.h"

CRITICAL_SECTION    gCs;
CRITICAL_SECTION    gRecvCs;
char    gData[MAX_BUFFER];
int     gDataLen  =0;
char    gRecv[RECVBUF_SIZE];
char    gPlayBuff[6][RECVBUF_SIZE*4];

int     gPlayBuffPtr=0;

int     gThreadQuit=0;

bool    bRecording=false;
bool    bPlaying  =false;

char    * gcdatatosend;

sockaddr_in gRemoteAddr;
sockaddr_in gRemoteUDP ;

int     gUdpPort=UDP_PORT;
int     gRemoteUdpPort=UDP_PORT;



HINSTANCE ghInst=NULL;

char     szClassName[ ] = "WindowsApp";
//HWAVEIN  hWaveIn;
//HWAVEOUT hWaveOut;
HWND     ghwnd;
//char     * cBuffer[6]={NULL,NULL,NULL,NULL,NULL,NULL};
int      nPaintNum=0;
char     * cPaint[20];


HANDLE   gCanSend;
HANDLE   gHaveData;
HANDLE   gCanRecv;
HANDLE   ghRecv;

HANDLE   gRecvThread;
HANDLE   gSendThread;

DWORD    gdwRecvPid;
DWORD    gdwSendPid;

void __cdecl FormatError(char * err,...)
{
     // 格式化输出函数  
     char temp[256];
     va_list vls;
     va_start(vls,err);
     _vsnprintf(temp,256,err,vls);
     va_end(vls);
     OutputDebugString(temp);
     
}

#endif
