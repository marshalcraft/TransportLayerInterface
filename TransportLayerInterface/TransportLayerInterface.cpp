#include "TransportLayerInterface.h"

#include "InitializeWinSockAPI.h"

DllExport void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt )
{
	WinSockAPI WindowSockets;
	InitializeWinSockAPI(&WindowSockets);
}
