#include "TransportLayerInterface.h"

#include "InitializeWinSockAPI.h"

DllExport void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt )
{
	WinSockAPI WindowSockets;
	WindowSockets.ServerInfReady = 0x00;

	InitializeWinSockAPI(&WindowSockets);

	if (WindowSockets.WinSockAPIReady == false)
	{
		// Tell main thread there is an error loading transport interface, file missing or incorrect version.
	}
	
	EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
	pAuxConSt->UnExactData.ServInf.InfoReady = WindowSockets.ServerInfReady;
	EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
	do 
	{
		EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
		pAuxConSt->UnExactData.ServInf.InfoReady = WindowSockets.ServerInfReady;
		EnterCriticalSection(&pAuxConSt->UnExactData.ServInf.TlsServerInfoLockObj);
	} 
	while (WindowSockets.ServerInfReady == 0x01);
}
