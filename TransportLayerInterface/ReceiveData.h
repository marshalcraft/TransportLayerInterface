#pragma once
#include "TransportLayerInterface.h"

#ifndef RECEIVEDATAHEADER
#define RECEIVEDATAHEADER
__inline void ReceiveData(_In_ PWinSockAPI WindowSockets, _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt)
{

	if (select(0, WindowSockets->PReadFds, NULL, NULL, WindowSockets->PRecvSelectHoldTime))
	{
		WindowSockets->RecvStatus = recv(WindowSockets->Socket, (char *)WindowSockets->RecvDataTemporaryStorage, WindowSockets->RecvDataTemporaryStorageSize, 0x00);
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