#pragma once
#include "TransportLayerInterface.h"

#ifndef SERVERINFOREADYHOLDHEADER
#define SERVERINFOREADYHOLDHEADER
__inline void ServerInfoReadyHold(_In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt, _In_ WinSockAPI WindowSockets)
{
	do
	{
		EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
		pAuxConSt->UnExactData.ServInf.InfoReady = WindowSockets.ServerInfReady;
		LeaveCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
	}
	while (WindowSockets.ServerInfReady != 0x01);
}
#endif