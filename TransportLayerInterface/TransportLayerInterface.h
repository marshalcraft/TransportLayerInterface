#pragma once
//#include "stdafx.h"
#include "TlsConnection.h"
#include "TlsServerInfo.h"
#include "TransportLayerInfo.h"
#include "InterThreadCommunication.h"
#include "winbase.h"
#include "winsock2.h"
#include "Inaddr.h"

#define DllExport __declspec(dllexport)

DllExport void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt);

typedef int(*WSASTARTUP)(WORD, LPWSADATA);
typedef int(*WSACLEANUP)();
typedef int(*HTONS)(u_short);
typedef int(*INETPTON)( INT, PCTSTR, PVOID);
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
	INETPTON inetPton;
	SOCKETS sockets;
	CONNECT connect;
	RECV recv;
	SEND send;
	WSAGETLASTERROR WSAGetLastError;
	FD_SET * PReadFds;

	timeval * PRecvSelectHoldTime;
	BYTE * RecvDataTemporaryStorage;
	BYTE RecvDataTemporaryStorageSize;

	int WinSockInitError;
	int ConnectionStatusOrError;
	int SendStatus;
	int RecvStatus;
	WSADATA WSAData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr_In;
	BYTE ConnectionTimeOut;
	BYTE ServerInfReady;

	bool WinSockAPIReady;
	bool SocketReady;
	bool ConnectionEstablished;
	bool TerminateSocket;
}WinSockAPI, * PWinSockAPI;

#ifndef INITIALIZEWINSOCKAPIHEADER
#define INITIALIZEWINSOCKAPIHEADER
__inline void InitializeWinSockAPI(_Inout_ PWinSockAPI winSockAPI)
{
	//******************************** Initialize WinSock2 Dll and functions ************************
	winSockAPI->ConnectionEstablished = false;
	winSockAPI->WinSockAPIReady = true;
	winSockAPI->hDll = LoadPackagedLibrary(TEXT("ws2_32.dll"), 0x00);

	if (winSockAPI->hDll == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Windows Socket Dynamic Link Library Loaded Successful.");
	}

	//*************************** Load WSAStartup() **********************************
	winSockAPI->WSAStartup = (WSASTARTUP)GetProcAddress(winSockAPI->hDll, "WSAStartup");
	if (winSockAPI->WSAStartup == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Windows Socket WSASTartup loaded Successfully.");
	}
	//************************** Load WSACleanup() ***********************************
	winSockAPI->WSACleanup = (WSACLEANUP)GetProcAddress(winSockAPI->hDll, "WSACleanup");
	if (winSockAPI->WSACleanup == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Windows Socket WSACleanup loaded Successfully.");
	}

	//************************* Load htons() *****************************************
	winSockAPI->htons = (HTONS)GetProcAddress(winSockAPI->hDll, "htons");
	if (winSockAPI->htons == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Windows Socket htons port converter loaded successfully.");
	}
	//************************** Load inet_pton() ************************************
	winSockAPI->inetPton = (INETPTON)GetProcAddress(winSockAPI->hDll, "inetPton");
	if (winSockAPI->inetPton == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Windows Socket idef_addr address converter loaded successfully.");
	}

	//*************************** Bind socket to transport service provider **********
	winSockAPI->sockets = (SOCKETS)GetProcAddress(winSockAPI->hDll, "socket");
	if (winSockAPI->sockets == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("The socket was successfully bound.");
	}
	//************************** Establish a TCP connection **************************
	winSockAPI->connect = (CONNECT)GetProcAddress(winSockAPI->hDll, "connect");
	if (winSockAPI->connect == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Winsock successfully loaded connection API.");
	}
	//******************** Sends data on established connection **********************
	winSockAPI->send = (SEND)GetProcAddress(winSockAPI->hDll, "send");
	if (winSockAPI->send == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Winsock successfully loaded send API.");
	}

	//******************** Recieve data on established connection ********************
	winSockAPI->recv = (RECV)GetProcAddress(winSockAPI->hDll, "recv");
	if (winSockAPI->recv == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Winsock successfully loaded recv API.");
	}
	//********************** Get the last Socket error on this thread ****************
	winSockAPI->WSAGetLastError = (WSAGETLASTERROR)GetProcAddress(winSockAPI->hDll, "WSAGetLastError");
	if (winSockAPI->WSAGetLastError == NULL)
	{
		winSockAPI->WinSockAPIReady = false;
	}
	else
	{
		//Console::WriteLine("Successfully loaded WSAGetLastError API.");
	}
	//Finished Dll Initialization ****************************************************
}
#endif
#ifndef INITIALIZESOCKETHEADER
#define INTIIALIZESOCKETHEADER
__inline void InitializeSocket(_Inout_ PWinSockAPI WindowSockets, _In_ int addressFamilySpec, _In_ int typeSpec, _In_ int protocol, _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt)
{
	//**** write method which convertes BYTE * to ip address string like "222.222.222.222"
	if (WindowSockets->inetPton(AF_INET, (PCTSTR)pAuxConSt->UnExactData.ServInf.IpAddress15Bytes, &pAuxConSt->UnExactData.ServInf.WinSockFormattedIPV4Address) != 1)
	{
		//handle address conversion error
	}
	WindowSockets->SockAddr_In.sin_addr.s_addr = pAuxConSt->UnExactData.ServInf.WinSockFormattedIPV4Address.S_un.S_addr;
	WindowSockets->SockAddr_In.sin_family = AF_INET;
	WindowSockets->SockAddr_In.sin_port = htons((0xFF * pAuxConSt->UnExactData.ServInf.Port[1]) + pAuxConSt->UnExactData.ServInf.Port[0]);
	WindowSockets->Socket = WindowSockets->sockets(addressFamilySpec, typeSpec, protocol);
	if (WindowSockets->Socket == INVALID_SOCKET)
	{
		//Handle Socket initialization error.
	}

	// For select() fd_set initialization for single socket.
	FD_ZERO(WindowSockets->PReadFds);
	FD_SET(WindowSockets->Socket, WindowSockets->PReadFds);
	WindowSockets->PRecvSelectHoldTime->tv_sec = 0x00;
	WindowSockets->PRecvSelectHoldTime->tv_usec = 0x10;

	WindowSockets->SocketReady = true;
}
#endif
#ifndef SERVERINFOREADYHOLDHEADER
#define SERVERINFOREADYHOLDHEADER
__inline void ServerInfoReadyHold(_In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt, _In_ WinSockAPI WindowSockets)
{
	do
	{
		EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
		pAuxConSt->UnExactData.ServInf.InfoReady = WindowSockets.ServerInfReady;
		LeaveCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
	} while (WindowSockets.ServerInfReady != 0x01);
}
#endif
#ifndef SENDDATAHEADER
#define SENDDATAHEADER

__inline void SendData(_In_ PWinSockAPI WindowSockets, _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt)
{
	WindowSockets->ConnectionStatusOrError = WindowSockets->connect(WindowSockets->Socket, (sockaddr *)&WindowSockets->SockAddr_In, sizeof(WindowSockets->SockAddr_In));
	if (WindowSockets->ConnectionStatusOrError != 0)
	{
		WindowSockets->ConnectionStatusOrError = WindowSockets->WSAGetLastError();
		if (WindowSockets->ConnectionStatusOrError != WSAEISCONN)
		{
			//handle tcp connection error
		}
	}

	EnterCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSend);
	if (pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerNewData == true)
	{
		WindowSockets->send(WindowSockets->Socket, (const char *) pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSendData, pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSendDataSize, 0);
		pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerNewData = false;
	}
	LeaveCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSend);

	EnterCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSend);
	if (pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitNewData == true)
	{
		WindowSockets->send(WindowSockets->Socket, (const char *)pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSendData, pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSendDataSize, 0);
		pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitNewData = false;
	}
	LeaveCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSend);

	EnterCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerThreadSend);
	if (pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerNewData == true)
	{
		WindowSockets->send(WindowSockets->Socket, (const char *)pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerThreadSendData, pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSendDataSize, 0);
		pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerNewData = false;
	}
	LeaveCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerThreadSend);
}
#endif
#ifndef RECEIVEDATAHEADER
#define RECEIVEDATAHEADER
__inline void ReceiveData(_In_ PWinSockAPI WindowSockets, _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt)
{

	if ( select(0, WindowSockets->PReadFds, NULL, NULL,  WindowSockets->PRecvSelectHoldTime))
	{
		WindowSockets->RecvStatus = recv( WindowSockets->Socket, (char *)WindowSockets->RecvDataTemporaryStorage, WindowSockets->RecvDataTemporaryStorageSize, 0x00);
		if (WindowSockets->RecvStatus == SOCKET_ERROR)
		{
			// Handle recv errors. 
		}
		if (WindowSockets->RecvStatus == 0)
		{
			// Handle connection graceful closures.
		}
		if (WindowSockets->RecvStatus != SOCKET_ERROR || WindowSockets->RecvStatus != 0)
		{
			EnterCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.RecvRdy.TransportRecvCS); // Ensure critical section initialized.
			pAuxConSt->UnExactData.IntrThrdPle.RecvRdy.DataBufferSize[0] = WindowSockets->RecvStatus; // Work this bullshit out.
			pAuxConSt->UnExactData.IntrThrdPle.RecvRdy.DataBuffer = WindowSockets->RecvDataTemporaryStorage;
			LeaveCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.RecvRdy.TransportRecvCS);
		}
	}
}
#endif