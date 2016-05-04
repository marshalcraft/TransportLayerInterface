#pragma once
#include "TlsConnection.h"

namespace TlsConnection
{
	typedef struct TransportLayerInfo
	{
		BYTE * TransportInterfaceDllName;
		BYTE TransportInterfaceDllNameSize;
	} TransportLayerInfo, *PTransportLayerInfo;
}