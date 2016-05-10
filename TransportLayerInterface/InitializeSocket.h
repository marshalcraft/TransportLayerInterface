#pragma once
#include "TransportLayerInterface.h"
#include "winbase.h"
#include "winsock2.h"

#ifndef INITIALIZESOCKETHEADER
#define INITIALIZESOCKETHEADER
__inline void InitializeSocket(_Inout_ PWinSockAPI WindowSockets, _In_ int addressFamilySpec, _In_ int typeSpec, _In_ int protocol)
{
	WindowSockets->Socket = WindowSockets->sockets(addressFamilySpec, typeSpec, protocol);
	if (WindowSockets->Socket == INVALID_SOCKET)
	{
		//Handle Socket initialization error.
	}
	WindowSockets->SocketReady = true;
}
#endif