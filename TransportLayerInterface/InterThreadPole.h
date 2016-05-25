#pragma once
typedef struct TransportRecvReady
{
	CRITICAL_SECTION TransportRecvCS;
	BYTE * DataBuffer;
	BYTE * DataBufferSize;
}TransportRecvReady, *PTransportRecvReady;

typedef struct TransportSendReady
{
	CRITICAL_SECTION HandShakeHandlerSend;
	bool HandShakeHandlerNewData;
	BYTE * HandShakeHandlerSendData;
	BYTE HandShakeHandlerSendDataSize;
	CRITICAL_SECTION ChangeCipherSuitThreadSend;
	bool ChangeCipherSuitNewData;
	BYTE * ChangeCipherSuitThreadSendData;
	BYTE ChangeCipherSuitThreadSendDataSize;
	CRITICAL_SECTION ApplicationLayerThreadSend;
	bool ApplicationLayerNewData;
	BYTE * ApplicationLayerThreadSendData;
	BYTE ApplicationLayerThreadSendDataSize;
}TransportSendReady, *PTransportSendReady;


typedef struct InterThreadPole
{
	TransportRecvReady RecvRdy;
	TransportSendReady SndRdy;
}InterThreadPole, *PInterThreadPole;
