
#ifndef ID_H
#define ID_H

#include <stdio.h>
#include <stdarg.h>
#include  <windows.h>

#define MM_SOCKETLISTEN  WM_USER + 1
#define MM_SOCKETDATA_CLIENT    WM_USER + 2
#define MM_SOCKETDATA_RECV      WM_USER + 3
#define MM_SOCKET_TEXT          WM_USER + 4 

#define UDP_PORT   5678
#define LISTEN_PORT    1024
#define B_SIZE (8000/4)
#define MAX_BUFFER       (1024*1024)
#define RECVBUF_SIZE     B_SIZE

#define ID_CONNECT 1024
#define ID_DECONNECT 1025

#define ID_SHOW     1405
#define ID_INPUT    1406
#define ID_SEND     1407

#define ID_IP       10024 

#define debug
#define Info(id)  MessageBox(NULL,id,"Information",MB_OK|MB_ICONINFORMATION)
#define Error(id) MessageBox(NULL,id,"Error",MB_OK)


#define OutPut(str,err) FormatError(str,err)
extern CRITICAL_SECTION    gCs;
extern CRITICAL_SECTION    gRecvCs;
extern char    gData[MAX_BUFFER];
extern int     gDataLen  ;
extern char    gRecv[RECVBUF_SIZE];
extern char    gPlayBuff[6][RECVBUF_SIZE*4];

extern int     gPlayBuffPtr;

extern int     gThreadQuit;
extern bool    bRecording;
extern bool    bPlaying  ;

extern char    * gcdatatosend;

extern sockaddr_in gRemoteAddr;
extern sockaddr_in gRemoteUDP;





extern HINSTANCE ghInst;

extern char     szClassName[ ] ;

extern HWND     ghwnd;

extern int      nPaintNum;
extern char     * cPaint[20];


extern HANDLE   gCanSend;
extern HANDLE   gHaveData;
extern HANDLE   gCanRecv;
extern HANDLE   ghRecv;

extern int      gUdpPort;
extern int      gRemoteUdpPort;
void __cdecl FormatError(char * err,...);

//class   Socket;

/*  old version

char    * Wave_GetBuffer(int );
int     WaveInit(void);
int     ProcessData(WAVEHDR * );

*/


#endif
