#pragma once
#include "TransportLayerInterface.h"
#include "winbase.h"
#include "winsock2.h"

#ifndef INITIALIZESOCKETHEADER
#define INITIALIZESOCKETHEADER
__inline void InitializeSocket(_Inout_ PWinSockAPI WindowSockets, _In_ int addressFamilySpec, _In_ int typeSpec, _In_ int protocol)
{
	WindowSockets->WinSockInitError = WindowSockets->WSAStartup(0x0202, &WindowSockets->WSAData);
	if (WindowSockets->WinSockInitError != 0)
	{
		// Handle WSAStartup failure.
	}
	WindowSockets->Socket = WindowSockets->sockets(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (WindowSockets->Socket == INVALID_SOCKET)
	{
		//Handle Socket initialization error.
	}
}
#endif