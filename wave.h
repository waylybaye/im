#ifndef _wave_h
#define _wave_h

#include <windows.h>

class WaveIn
{
    public:
    int          Init();
    private:
    char   *     cBuffer[6];
    HWAVEIN      m_hWaveIn;
    WAVEFORMATEX m_wfmt;
    WAVEHDR      m_whdr[6];
    MMRESULT     m_nRet;
    int          m_nBSize;
    public:
    WaveIn();
    ~WaveIn();
    
    char*GetBuffer(int      i  );
    int  AddBuffer(WAVEHDR *hdr);
    int  Init     (HWND        );
    int  Start();
    void Clean();
    int  Close();
    MMRESULT GetRet();
    int  PrepareHeader(WAVEHDR*);
    int  UnPrepareHeader(WAVEHDR *);
};

class WaveOut
{   
    private:
    WAVEFORMATEX m_wfmt;
    HWAVEOUT     m_hWaveOut;
    WAVEHDR      m_whdr[6];
    
    int          m_whdrPtr;
    
    MMRESULT     m_nRet;
    char         pBuff[6];
    public:
    int Init(HWND );
    int Close()    ;
    int Reset()    ;
    int Write(char * ,size_t);
    
    
    MMRESULT GetRet();
    
    WaveOut();
    ~WaveOut();
    
    
};

#endif
