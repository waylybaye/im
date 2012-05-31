#ifndef _WAVE_CPP
#define _WAVE_CPP
#include <windows.h>
#include "id.h"
#include "wave.h"





MMRESULT WaveIn::GetRet()
{
    return m_nRet;
}

WaveIn::~WaveIn()
{
    Close();
}

WaveIn::WaveIn()
{
    m_hWaveIn=NULL;
    for(int i=0;i<6;i++){
            cBuffer[i]=NULL;
            }
    m_nBSize=8000/4;
}


             
int WaveIn::Init(HWND hwnd)
{   
    //MMRESULT rtn=MMSYSERR_NOERROR;
    
    m_wfmt.wFormatTag=WAVE_FORMAT_PCM;
    m_wfmt.nChannels =1;
    m_wfmt.nSamplesPerSec=8000;
    m_wfmt.nAvgBytesPerSec=8000;
    m_wfmt.nBlockAlign=1;
    m_wfmt.wBitsPerSample=8;
    m_wfmt.cbSize=0;
    m_nRet=waveInOpen(&m_hWaveIn,WAVE_MAPPER,&m_wfmt,(DWORD)hwnd,0,CALLBACK_WINDOW);
    if(m_nRet!=MMSYSERR_NOERROR){
                              #ifdef debug
                              Error("Error In waveInOpen");
                              switch(m_nRet){
                                          case MMSYSERR_NODRIVER:
                                               MessageBox(NULL,"Return 'MMSYSERR_NODRIVER' ","Error",MB_OK);
                                               break;
                                          case MMSYSERR_ALLOCATED:
                                               Error("MMSYSERR_ALLOCATED");
                                               break;
                                          case WAVERR_BADFORMAT:
                                               Error("MMSYSERR_BADFORMAT");
                                               break;
                                          case MMSYSERR_NOMEM:
                                               Error("SYSERR_NOMEM");
                                               break;
                                          case MMSYSERR_BADDEVICEID:
                                               Error("MMSYAERR_BADDEVICEID");
                                               break;
                                          case MMSYSERR_INVALPARAM:
                                               Error("MMSYSERR_INVALPARAM");
                                               break;
                                          }
                              #endif
                              return 0;
                              }
    
                              
    if(m_hWaveIn==NULL){
                      return 0;
                      }
    
    
    
    for(int i=0;i<6;i++){   
            m_whdr[i].dwBufferLength=m_nBSize;
            m_whdr[i].dwUser=0;
            m_whdr[i].dwFlags=0;
            m_whdr[i].dwBytesRecorded=0;
            m_whdr[i].dwLoops=1;
            m_whdr[i].reserved=0;
            m_whdr[i].lpNext=NULL;

            m_whdr[i].lpData=GetBuffer(i);
            if(m_whdr[i].lpData==NULL){
                     MessageBox(NULL,"Error in alloc memories ","Error",MB_OK);
                     waveInClose(m_hWaveIn);
                     return 0;
                     }
            
            m_nRet=waveInPrepareHeader(m_hWaveIn,&(m_whdr[i]),sizeof(m_whdr[i]));
            if(m_nRet!=MMSYSERR_NOERROR){
                    if(m_hWaveIn!=NULL){
                            waveInClose(m_hWaveIn);
                            }
                    return 0;
                    }
            if(!AddBuffer    (&(m_whdr[i]))){
            //if(m_nRet!=MMSYSERR_NOERROR){
                    if(m_hWaveIn!=NULL){
                            waveInUnprepareHeader(m_hWaveIn,&(m_whdr[i]),sizeof(m_whdr[i]));
                            waveInClose(m_hWaveIn);
                            }
                    return 0;
                    }
            
            }
     return 1;
                

}

int WaveIn::AddBuffer(WAVEHDR *hdr)
{
    //MMRESULT rtn;
    //int      nRet=1;
    m_nRet=waveInAddBuffer(m_hWaveIn,hdr,sizeof(WAVEHDR));
    if(m_nRet!=MMSYSERR_NOERROR){
         return 0;
         }
    return 1;
}


//  above is current version 


int WaveOut::Init(HWND hwnd)
{
    //MMRESULT rtn=MMSYSERR_NOERROR;
    
    m_wfmt.wFormatTag=WAVE_FORMAT_PCM;
    m_wfmt.nChannels =1;
    m_wfmt.nSamplesPerSec=8000;
    m_wfmt.nAvgBytesPerSec=8000;
    m_wfmt.nBlockAlign=1;
    m_wfmt.wBitsPerSample=8;
    m_wfmt.cbSize=0;
    m_nRet=waveOutOpen(&m_hWaveOut,WAVE_MAPPER,&m_wfmt,(DWORD)hwnd,0,CALLBACK_WINDOW);
    if(m_nRet!=MMSYSERR_NOERROR){
                              //Error("Failed to Call waveOutOpen");
                              return 0;
                              }
    
    return 1;
}


char * WaveIn::GetBuffer(int i)
{
    
     
     if(i>5){
             return NULL;
             }
     if(cBuffer[i]==NULL){
             
             cBuffer[i]=(char*)malloc(m_nBSize);
             }
     if(cBuffer[i]==NULL){
             return NULL;
             }
      return cBuffer[i];  

} 

     
void WaveIn::Clean()
{
                     for(int i=0;i<6;i++){
                         if(GetBuffer(i)!=NULL){
                                  free(GetBuffer(i));
                                  }
                         }
                          
}

int WaveIn::Close()
{
    //int nRet;
    Clean();
    if(m_hWaveIn!=NULL){
                        
          m_nRet=waveInClose(m_hWaveIn);
          if(m_nRet!=MMSYSERR_NOERROR){
               return 0;
               }
          }
    return 1;
}

int WaveIn::Start()
{
    //int nRet;
    if(m_hWaveIn!=NULL){
           m_nRet=waveInStart(m_hWaveIn);
           if(m_nRet!=MMSYSERR_NOERROR){
                  return 0;
                  }
    }
    return 1;
}

int WaveIn::PrepareHeader(WAVEHDR *hdr)
{   
    waveInPrepareHeader(m_hWaveIn,hdr,sizeof(WAVEHDR));
}

int WaveIn::UnPrepareHeader(WAVEHDR *hdr)
{
    waveInUnprepareHeader(m_hWaveIn,hdr,sizeof(WAVEHDR));
}

WaveOut::WaveOut()
{
    m_hWaveOut=NULL;
    m_whdrPtr=0;
}

int WaveOut::Write(char * lpData,size_t len)
{
    if(len<=0){
              return 0;
              }
    
    m_whdr[m_whdrPtr].dwBufferLength=len;
    m_whdr[m_whdrPtr].dwUser=0;
    m_whdr[m_whdrPtr].dwFlags=0;
    m_whdr[m_whdrPtr].dwBytesRecorded=0;
    m_whdr[m_whdrPtr].dwLoops=1;
    m_whdr[m_whdrPtr].reserved=0;
    m_whdr[m_whdrPtr].lpNext=NULL;
    m_whdr[m_whdrPtr].lpData=lpData;
    
    m_nRet=waveOutPrepareHeader(m_hWaveOut,&m_whdr[m_whdrPtr],sizeof(m_whdr));
    if(m_nRet!=MMSYSERR_NOERROR){
                              //Error("waveOutPrepareHeader");
                              FormatError("Error when OutPrepareHeader,in WaveOut::Write,Code %d ",(int)m_nRet);
                              return 0;
                              }
                              
    m_nRet=waveOutWrite(m_hWaveOut,&m_whdr[m_whdrPtr],sizeof(m_whdr));
    if(m_nRet!=MMSYSERR_NOERROR){
                              //Error("waveOutWrite");
                              FormatError("Error when OutWrite ,in WaveOut.cpp , Code : %d ",(int)m_nRet);
                              return 0;
                              }
    m_whdrPtr=(m_whdrPtr+1)%6;
    return 1;
    
}
                

int WaveOut::Reset()
{
    //int rtn;
    m_nRet=waveOutReset(m_hWaveOut);
    if(m_nRet!=MMSYSERR_NOERROR){
          return 0;
          }
          
    return 1;
}

int WaveOut::Close()
{
    //int rtn;
    m_nRet=waveOutClose(m_hWaveOut);
    if(m_nRet!=MMSYSERR_NOERROR){
          return 0;
          }
    return 1;
}

MMRESULT WaveOut::GetRet()
{
     return m_nRet;
}

WaveOut::~WaveOut()
{
     if(m_hWaveOut!=NULL){
           m_nRet=waveOutClose(m_hWaveOut);
           }
}

#endif
