#ifndef _sock_h
#define _sock_H

#include <windows.h>

class SocketInit
{   public:
    
     SocketInit()
    {
                
    
                if(WSAStartup((1<<8|1),&m_wsa)!=0){
                                                 m_bInit=false;
                                                 ExitProcess(0);
                                                 }
    }
     ~SocketInit()
    {          if(m_bInit){
               
                           WSACleanup();
                           }
    }
    private:
    WSADATA m_wsa;
    bool    m_bInit;
    
    public:
           
    int Inited()
    { 
        return m_bInit;
    } 
};      
                                     
          
class Socket
{   
    public:
    Socket(SOCKET s);
    Socket();
    ~Socket();
    private:
    SOCKET m_sock;
    sockaddr_in m_remote;
    
    public:
    int    Init();
    int    Close();
    bool   Connected();
    
    
    int    operator ==(SOCKET n);
    int    operator = (SOCKET n);
    
    int    AsyncSelect(HWND,unsigned int ,long );
    int    Create  (int type=SOCK_STREAM );
    
    int    Bind    (short  );
    int    Connect (char *ip,int );
    int    Listen  (void);
    SOCKET Accept  ();
    void   Clean   ();
    int    Send    (char *,int );
    int    Recv    (char *,int );
    
    int    Sendto  (char *,size_t,sockaddr_in *);
    int    Sendto  (char *,size_t,char* ,short);
    int    Recvfrom(char *,size_t,sockaddr_in *,int *);
    
    int    GetPeerName(sockaddr_in * addr);
    int    GetPeerName(char * ip );
    
};

#endif
