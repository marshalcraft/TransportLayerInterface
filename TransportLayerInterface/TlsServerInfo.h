#pragma once
#include "TlsConnection.h"
namespace TlsConnection
{
	typedef struct TlsServerInfo
	{
		CRITICAL_SECTION TlsServerInfoLockObj;
		BYTE * IpAddressFourBytes;
		BYTE * DomainName;
		BYTE * DomainNameSize;
		BYTE * Port;
		BYTE InfoReady;
	}TlsServerInfo, *PTlsServerInfo;
}