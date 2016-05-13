#pragma once
#include "TransportLayerInterface.h"

#ifndef SENDDATAHEADER
#define SENDDATAHEADER

__inline void SendData(_In_ PWinSockAPI WindowSockets, _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt)
{	
	WindowSockets->ConnectionStatusOrError = WindowSockets->connect(WindowSockets->Socket, (sockaddr *)&WindowSockets->SockAddr_In, sizeof(WindowSockets->SockAddr_In));
	if (WindowSockets->ConnectionStatusOrError != 0)
	{
		WindowSockets->ConnectionStatusOrError = WindowSockets->WSAGetLastError();
		if (WindowSockets->ConnectionStatusOrError != )
		{
			//handle tcp connection error
		}
	}
}
#endif
