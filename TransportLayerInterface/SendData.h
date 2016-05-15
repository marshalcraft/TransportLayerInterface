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
		if (WindowSockets->ConnectionStatusOrError != WSAEISCONN)
		{
			//handle tcp connection error
		}
	}

	EnterCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSend);
	if (pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerNewData == true)
	{
		WindowSockets->send(WindowSockets->Socket, (const char *)pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSendData, pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSendDataSize, 0);
		pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerNewData = false;
	}
	LeaveCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSend);

	EnterCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSend);
	if (pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitNewData == true)
	{
		WindowSockets->send(WindowSockets->Socket, (const char *)pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSendData, pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSendDataSize, 0);
		pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerNewData = false;
	}
	LeaveCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSend);

	EnterCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerThreadSend);
	if (pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerNewData == true)
	{
		WindowSockets->send(WindowSockets->Socket, (const char *)pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ApplicationLayerThreadSendData, pAuxConSt->UnExactData.IntrThrdPle.SndRdy.ChangeCipherSuitThreadSendDataSize, 0);
		pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerNewData = false;
	}
	LeaveCriticalSection(&pAuxConSt->UnExactData.IntrThrdPle.SndRdy.HandShakeHandlerSend);
}
#endif
