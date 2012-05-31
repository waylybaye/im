#ifndef _SOCK_CPP
#define _SOCK_CPP

#include <windows.h>
#include <winsock.h>


#include "sock.h"






bool Socket::Connected()
{
     if(m_sock!=INVALID_SOCKET){
             return true;
     }else{

     return false;
     }
}

int Socket::Create(int type)
{
    m_sock=socket(AF_INET,type,0);
    if(m_sock==INVALID_SOCKET){
            return 0;
            }
    return 1;
}

int Socket::Listen()
{
    if(listen(m_sock,5)==SOCKET_ERROR){
            return 0;}
    return 1;

}

int Socket::Bind(short port)
{
    sockaddr_in inetaddr;
    inetaddr.sin_addr.s_addr=INADDR_ANY;
    inetaddr.sin_family     =AF_INET;
    inetaddr.sin_port       =htons(port);
    
    if(bind(m_sock,(SOCKADDR *)&inetaddr,sizeof(inetaddr))==SOCKET_ERROR){
            return 0;
            }
    return 1;
    
}


int Socket::AsyncSelect(HWND hwnd,unsigned int message,long fd)
{
    int nRet;
    nRet=WSAAsyncSelect(m_sock,hwnd,message ,fd);
    if(nRet==SOCKET_ERROR){
            return 0;
            }
    return 1;
}

int Socket::Connect(char * ip,int port)
{    
     
     
     m_remote.sin_addr.s_addr=inet_addr(ip);
     m_remote.sin_port=htons(port);
     m_remote.sin_family=AF_INET;
     if(connect(m_sock,(sockaddr*)&m_remote,sizeof(m_remote))==SOCKET_ERROR){
               return 0;
               }
     
     //WSAAsyncSelect(sock,ghwnd,MM_SOCKETDATA,FD_READ|FD_WRITE|FD_CLOSE);
     return 1;
}
     
SOCKET Socket::Accept()
{
    SOCKET   sock;
    int      addrlen;
    sock=accept(m_sock,(sockaddr*)&m_remote,&addrlen);
     
    //if(sock==INVALID_SOCKET){
    //        return 0;
    //        }
    
    return sock;
    
}

int Socket::operator = (SOCKET n)
{
    m_sock=n;
	return m_sock;
}


int Socket::operator ==(SOCKET  n)
{
    if(m_sock==n){
                  return 1;
                  }
    return 0;
}


Socket::Socket()
{
    m_sock=INVALID_SOCKET;
}


Socket::Socket(SOCKET s)
{
    m_sock=s;
}

Socket::~Socket()
{
     Clean();
}

void Socket::Clean()
{
     if(m_sock!=INVALID_SOCKET){
            closesocket(m_sock);
            }
     
     
}
                
int Socket::Send(char * data, int len)
{
    int nRet;
    if(len<0){
              return 0;
              }
    
    
    if(Connected()){
                    
                    nRet=send(m_sock,data,len,0) ;
                    return nRet; 
                    }
    else{
         
         return -1;
         }
     
    

}

int Socket::Close()
{
    if(m_sock!=INVALID_SOCKET){
          closesocket(m_sock);
          }
	return 1;
}

int Socket::Recv  (char *buff, int len)
{
    int nRet;
    nRet=recv(m_sock,buff,len,0);
    return nRet;
}

int Socket::Sendto(char * data ,size_t datalen,sockaddr_in *addr)
{
    if(datalen<=0){
          return 0;
          }
    int nRet=sendto(m_sock,data,datalen,0,(SOCKADDR*)addr,sizeof(sockaddr_in));
    return nRet;
}

int Socket::Sendto(char * data ,size_t datalen,char * ip,short port)
{
    int nRet;
    sockaddr_in addr;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port       =htons(port);
    addr.sin_family     =AF_INET;
    
    nRet=sendto(m_sock,data,datalen,0,(sockaddr*)&addr,sizeof(addr));
    return nRet;
}

int Socket::Recvfrom(char * buf,size_t buflen,sockaddr_in *addr,int* len)
{
    int nRet;
    
    nRet=recvfrom(m_sock,buf,buflen,0,(SOCKADDR *)addr,len);
    return nRet;
}

int Socket::GetPeerName(sockaddr_in * addr)
{
    int nlen=sizeof(sockaddr_in);
    if(getpeername(m_sock,(sockaddr*)addr,&nlen)==SOCKET_ERROR){
          return 0;
          }
    return 1;
}

int Socket::GetPeerName(char * ip)
{
    int len=sizeof(sockaddr_in);
    sockaddr_in addr;
    if(getpeername(m_sock,(sockaddr*)&addr,&len)==SOCKET_ERROR){
          return 0;
          }
    strcpy(ip,inet_ntoa(addr.sin_addr));
    return 1;
}

//  Add after multiThread     

    
#endif
