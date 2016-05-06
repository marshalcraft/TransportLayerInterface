#pragma once
typedef struct TransportRecvReady
{
	bool HandShakeHandlerRead;
	bool ChangeCipherSuitThreadRead;
	bool ApplicationLayerThreadRead;
	BYTE * DataBuffer;
	BYTE * DataBufferSize;
}TransportRecvReady, *PTransportRecvReady;

typedef struct TransportSendReady
{
	bool HandShakeHandlerSend;
	BYTE * HandShakeHandlerSendData;
	BYTE * HandShakeHandlerSendDataSize;
	bool ChangeCipherSuitThreadSend;
	BYTE * ChangeCipherSuitThreadSendData;
	BYTE * ChangeCipherSuitThreadSendDataSize;
	bool ApplicationLayerThreadSend;
	BYTE * ApplicationLayerThreadSendData;
	BYTE * ApplicationLayerThreadSendDataSize;
}TransportSendReady, *PTransportSendReady;
typedef struct InterThreadPole
{
	TransportRecvReady RecvRdy;
	TransportSendReady SndRdy;
}InterThreadPole, *PInterThreadPole;
