#pragma once
#include "TransportLayerInterface.h"

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