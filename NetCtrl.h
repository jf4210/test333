#define		TCP_PACKET_MAXSIZE		8192			//1460
#define		TCP_RECV_BUFF			(1024*1024*5)
#define		TCP_SEND_BUFF			(1024*1024*5)
#define		UDP_MAX_BUFFSIZE		800

// ‰≥ˆ
class IUdpClientNotify
{
public:
	virtual void OnUdpClientNotifyReceivedData(const char* pData,int nLen,const char* pAddr,unsigned short usPort)=0;
};

// ‰»Î
class IUdpClient
{
public:
	virtual void ReleaseConnections(void)=0;
	virtual void SendData(const char* pData,int nLen,unsigned long ulIP,unsigned short usPort)=0;
};
extern "C" __declspec(dllexport) IUdpClient * CreateUdpClient(IUdpClientNotify& rNotify,unsigned short usPort);



class ITcpClientNotify
{
public:
	virtual void OnTcpClientNotifyReceivedData(const char* pData,int nLen)=0;
	virtual void OnTcpClientNotifyTime(DWORD dwTime) = 0;
	virtual	void OnTcpClientNotifyDisconnect(UINT uSocket)=0;
};

class ITcpClient
{
public:
	virtual void ReleaseConnections(void)=0;
	virtual int  SendData(const char* pData,int nLen)=0;
	virtual	void GetLocalHostAddr(char *pAddr)=0;
};

extern "C" __declspec(dllexport) ITcpClient * CreateTcpClient(ITcpClientNotify& rNotify,const char* szAddr, unsigned short usPort);

class ITcpServerNotify
{
public:
	virtual void OnTcpServerNotifyReceivedData(const char* pData,int nLen,UINT uSocket)=0;
	virtual	void OnTcpServerNotifyDisconnect(UINT uSocket)=0;
};

class ITcpServer
{
public:
	virtual void ReleaseConnections(void)=0;
	virtual int  SendData(const char* pData,int nLen,UINT uSocket)=0;
	virtual	void GetLocalHostAddr(char *pAddr)=0;
};

extern "C" __declspec(dllexport) ITcpServer * CreateTcpServer(ITcpServerNotify& rNotify,unsigned short usPort);
