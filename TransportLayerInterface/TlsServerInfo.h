#pragma once
#include "TlsConnection.h"
namespace TlsConnection
{
	typedef struct TlsServerInfo
	{
		BYTE * IpAddressFourBytes;
		BYTE * DomainName;
		BYTE * Port;
		BYTE InfoReady;
	}TlsServerInfo, *PTlsServerInfo;
}