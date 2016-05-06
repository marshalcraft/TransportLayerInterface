#pragma once
//#include "stdafx.h"
#include "TlsConnection.h"
#include "TlsServerInfo.h"
#include "TransportLayerInfo.h"
#include "InterThreadCommunication.h"
#include "winbase.h"
#include "winsock2.h"

#define DllExport __declspec(dllexport)

DllExport void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt);

typedef int(*WSASTARTUP)(WORD, LPWSADATA);
typedef int(*WSACLEANUP)();
typedef int(*HTONS)(u_short);
typedef unsigned long(*INET_ADDR)(char*);
typedef SOCKET(*SOCKETS)(int, int, int);
typedef int(*CONNECT)(SOCKET, sockaddr*, int);
typedef int(*RECV)(SOCKET, char*, int, int);
typedef int(*SEND)(SOCKET, const char*, int, int);
typedef int(*WSAGETLASTERROR)(void);

typedef struct WinSockAPI
{
	HINSTANCE hDll;
	BOOL DllHInstanceStatus;
	BOOL WinSockStatus;
	WSASTARTUP WSAStartup;
	WSACLEANUP WSACleanup;
	HTONS htons;
	INET_ADDR inet_addr;
	SOCKETS sockets;
	CONNECT connect;
	RECV recv;
	SEND send;
	WSAGETLASTERROR WSAGetLastError;
}WinSockAPI, * PWinSockAPI;

#ifndef INITIALIZEWINSOCKAPIHEADER
#define INITIALIZEWINSOCKAPIHEADER
__inline void InitializeWinSockAPI(_Inout_ PWinSockAPI winSockAPI)
{

}
#endif
