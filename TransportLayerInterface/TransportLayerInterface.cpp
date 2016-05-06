#include "TransportLayerInterface.h"

#include "InitializeWinSockAPI.h"

DllExport void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt )
{
	BYTE ServerInfReady = 0x00;
	WinSockAPI WindowSockets;
	InitializeWinSockAPI(&WindowSockets);
	if (WindowSockets.WinSockAPIReady == false)
	{
		// Tell main thread there is an error loading transport interface, file missing or incorrect version.
	}
	else
	{
		while (ServerInfReady == 0x01)
		{
			EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
			pAuxConSt->UnExactData.ServInf.InfoReady = ServerInfReady;
			EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
		}
	}
}
