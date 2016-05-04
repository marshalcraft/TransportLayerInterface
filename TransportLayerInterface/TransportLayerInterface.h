#pragma once
//#include "stdafx.h"
#include "TlsConnection.h"
#include "TlsServerInfo.h"
#include "TransportLayerInfo.h"
#include "InterThreadCommunication.h"

void TransportLayerInterface( _In_ TlsConnection::PAuxillaryConnectionStateData pAuxConSt);

typedef struct WinSockAPI
{

}WinSockAPI, *PWinSockAPI;