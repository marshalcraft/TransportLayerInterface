#include "TransportLayerInterface.h"

#include "InitializeWinSockAPI.h"

DllExport void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt )
{
	WinSockAPI WindowSockets;
	WindowSockets.ServerInfReady = 0x00;

	InitializeWinSockAPI(&WindowSockets);
	//pAuxConSt->UnExactData
	if (WindowSockets.WinSockAPIReady == false)
	{
		// Tell main thread there is an error loading transport interface, file missing or incorrect version.
	}

	WindowSockets.WinSockInitError = WindowSockets.WSAStartup(0x0202, &WindowSockets.WSAData);
	if (WindowSockets.WinSockInitError != 0)
	{
		// Handle WSAStartup failure.
	}
	do
	{
		ServerInfoReadyHold(pAuxConSt, WindowSockets);
		if (WindowSockets.SocketReady == false)
		{
			InitializeSocket( &WindowSockets, AF_INET, SOCK_STREAM, IPPROTO_TCP, pAuxConSt);//Generalize and use serverinfo to use other kinds of sockets.
		}
		SendData(&WindowSockets, pAuxConSt);
		//ReceiveData();

	}
	while (WindowSockets.TerminateSocket == false);

}
