#pragma once
#include "TlsConnection.h"
#include "Inaddr.h"
namespace TlsConnection
{
	typedef struct TlsServerInfo
	{
		CRITICAL_SECTION TlsServerInfoLockObj;
		BYTE * IpAddressFourBytes;
		BYTE * IpAddress15Bytes;
		IN_ADDR WinSockFormattedIPV4Address;
		BYTE * DomainName;
		BYTE * DomainNameSize;
		BYTE * Port;
		BYTE InfoReady;
	}TlsServerInfo, *PTlsServerInfo;
}
