#pragma once
#include <Windows.h>
#include "InterThreadCommunication.h"
#include "TlsServerInfo.h"
#include "TransportLayerInfo.h"
#include "InterThreadPole.h"

namespace TlsConnection // Each tcp connection shall be a process managed by tls manager.
{
	typedef struct SupportedCipherSuitDllPlugin
	{
		BYTE * CertificateAutheticationProtocol;
		BYTE * KeyExchangeProtocol;
		BYTE * BulkEncryptionProtocol;
		BYTE * MessageAuthenticationPrtocol;
	}SupportedCipherSuitDllPlugin, *PSupportedCipherSuitDllPlugin;

	typedef struct SupportedCipherSuitDllNameTable
	{
		PSupportedCipherSuitDllPlugin CipherSuits;
		BYTE * Size;
	}SupportedCipherSuitDllNameTable, *PSupportedCipherSuitDllNameTable;

	typedef struct AuxillaryData
	{
		BYTE * ClientRandom;
		BYTE * ServerRandom;

		HANDLE HandShakeThread;
		HANDLE ChangeCipherSpecThread;
		HANDLE AlertThread;
		HANDLE HeartBeatThread;

		SIZE_T HandShakeThreadStackSize;
		SIZE_T ChangeCipherSpecStackSize;
		SIZE_T AlertStackSize;
		SIZE_T HeartBeatStackSize;

		LPTHREAD_START_ROUTINE HandShakeFuncAddress;

		LPDWORD HandShakeThreadId;

		TlsServerInfo ServInf;

		InterThreadCommunication StVars;

		TransportLayerInfo TrnsPrtLyrInf;

		InterThreadPole IntrThrdPle;

	}AuxillaryData, PAuxillaryData; 
	
	typedef struct AuxillaryConnectionStateData
	{
		BYTE MajorVersion;
		BYTE MinorVersion;
		BYTE * CipherSuite;
		BYTE * SessionId;
		BYTE CompressionMethod;
		AuxillaryData UnExactData;

		SupportedCipherSuitDllNameTable ConnectionSupportedCipherSuitDllNameTable;

        
	}AuxillaryConnectionStateData, *PAuxillaryConnectionStateData; //Main Connection state structure.

	typedef struct TlsEncryptionCompressionState
	{
		AuxillaryConnectionStateData Current;
		AuxillaryConnectionStateData Pending;
	}TlsEncryptionCompressionState, *PTlsEncryptionCompressionState;


	void ConnectionRun( _In_ TlsServerInfo ServInf, _In_ TransportLayerInfo TrnsPrtLyrInf ); //Start a new process for each connection. Should return handle to the process or something.
}