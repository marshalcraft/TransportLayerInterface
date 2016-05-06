#include "TransportLayerInterface.h"

DllExport void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt )
{
	PWinSockAPI WindowSockets;
	InitializeWinSockAPI(&WindowSockets);
}
