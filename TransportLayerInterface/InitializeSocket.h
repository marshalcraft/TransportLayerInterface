#pragma once
#include "TransportLayerInterface.h"
//#include "winbase.h"
//#include "winsock2.h"

#ifndef INITIALIZESOCKETHEADER
#define INITIALIZESOCKETHEADER
__inline void InitializeSocket(_Inout_ PWinSockAPI WindowSockets, _In_ int addressFamilySpec, _In_ int typeSpec, _In_ int protocol, _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt)
{
	//**** write method which convertes BYTE * to ip address string like "222.222.222.222"
	if (WindowSockets->inetPton(AF_INET, (PCTSTR)pAuxConSt->UnExactData.ServInf.IpAddress15Bytes, &pAuxConSt->UnExactData.ServInf.WinSockFormattedIPV4Address) != 1)
	{
		//handle address conversion error
	}
	WindowSockets->SockAddr_In.sin_addr.s_addr = pAuxConSt->UnExactData.ServInf.WinSockFormattedIPV4Address.S_un.S_addr;
	WindowSockets->SockAddr_In.sin_family = AF_INET;
	WindowSockets->SockAddr_In.sin_port = htons((0xFF * pAuxConSt->UnExactData.ServInf.Port[1]) + pAuxConSt->UnExactData.ServInf.Port[0]);
	WindowSockets->Socket = WindowSockets->sockets(addressFamilySpec, typeSpec, protocol);
	if (WindowSockets->Socket == INVALID_SOCKET)
	{
		//Handle Socket initialization error.
	}
	WindowSockets->SocketReady = true;
}
#endif