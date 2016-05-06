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
	//******************************** Initialize WinSock2 Dll and functions ************************

	winSockAPI->hDll = LoadPackagedLibrary(TEXT("ws2_32.dll"), 0x00);

	if (winSockAPI->hDll == NULL)
	{
		//Console::WriteLine("Failed to load Windows Sockets Dll. The Dll is either missing or incorrect.");
	}
	else
	{
		//Console::WriteLine("Windows Socket Dynamic Link Library Loaded Successful.");
	}

	//*************************** Load WSAStartup() **********************************
	winSockAPI->WSAStartup = (WSASTARTUP)GetProcAddress(winSockAPI->hDll, "WSAStartup");
	if (winSockAPI->WSAStartup == NULL)
	{
		//Console::WriteLine("Failed to load Windows Socket WSASTartup.");
	}
	else
	{
		//Console::WriteLine("Windows Socket WSASTartup loaded Successfully.");
	}
	//************************** Load WSACleanup() ***********************************
	winSockAPI->WSACleanup = (WSACLEANUP)GetProcAddress(winSockAPI->hDll, "WSACleanup");
	if (winSockAPI->WSACleanup == NULL)
	{
		//Console::WriteLine("Failed to load Widnows Socket WSACleanup.");
	}
	else
	{
		//Console::WriteLine("Windows Socket WSACleanup loaded Successfully.");
	}

	//************************* Load htons() *****************************************
	winSockAPI->htons = (HTONS)GetProcAddress(winSockAPI->hDll, "htons");
	if (winSockAPI->htons == NULL)
	{
		//Console::WriteLine("Failed to load htons port converter");
	}
	else
	{
		//Console::WriteLine("Windows Socket htons port converter loaded successfully.");
	}
	//************************** Load inet_addr() ************************************
	winSockAPI->inet_addr = (INET_ADDR)GetProcAddress(winSockAPI->hDll, "inet_addr");
	if (winSockAPI->inet_addr == NULL)
	{
		//Console::WriteLine("Failed to load idef_addr address converter.");
	}
	else
	{
		//Console::WriteLine("Windows Socket idef_addr address converter loaded successfully.");
	}

	//*************************** Bind socket to transport service provider **********
	winSockAPI->sockets = (SOCKETS)GetProcAddress(winSockAPI->hDll, "socket");
	if (winSockAPI->sockets == NULL)
	{
		//Console::WriteLine("There was a problem with socket binding");
	}
	else
	{
		//Console::WriteLine("The socket was successfully bound.");
	}
	//************************** Establish a TCP connection **************************
	winSockAPI->connect = (CONNECT)GetProcAddress(winSockAPI->hDll, "connect");
	if (winSockAPI->connect == NULL)
	{
		//Console::WriteLine("Unable to load connection API from the dll.");
	}
	else
	{
		//Console::WriteLine("Winsock successfully loaded connection API.");
	}
	//******************** Sends data on established connection **********************
	winSockAPI->send = (SEND)GetProcAddress(winSockAPI->hDll, "send");
	if (winSockAPI->send == NULL)
	{
		//Console::WriteLine("Unable to load send API from the dll.");
	}
	else
	{
		//Console::WriteLine("Winsock successfully loaded send API.");
	}

	//******************** Recieve data on established connection ********************
	winSockAPI->recv = (RECV)GetProcAddress(winSockAPI->hDll, "recv");
	if (winSockAPI->recv == NULL)
	{
		//Console::WriteLine("Unable to load recv API from the dll.");
	}
	else
	{
		//Console::WriteLine("Winsock successfully loaded recv API.");
	}
	//********************** Get the last Socket error on this thread ****************
	winSockAPI->WSAGetLastError = (WSAGETLASTERROR)GetProcAddress(winSockAPI->hDll, "WSAGetLastError");
	if (winSockAPI->WSAGetLastError == NULL)
	{
		//Console::WriteLine("There was a problem loading WSAGetLastError from the dll.");
	}
	else
	{
		//Console::WriteLine("Successfully loaded WSAGetLastError API.");
	}
	//Finished Dll Initialization ****************************************************
}
#endif
