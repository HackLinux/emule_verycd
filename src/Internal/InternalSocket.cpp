/** @file InternalSocket.h @brief find the file you wanted in the internalnet 
<pre>
*	Copyright (c) 2007��Emule
*	All rights reserved.
*
*	��ǰ�汾��
*	��    �ߣ�kernel
*	������ڣ�2007-01-11
*
*	ȡ���汾��none
*	��    �ߣ�none
*	������ڣ�none
</pre>*/

#include "stdafx.h"
#include "InternalSocket.h"



CInternalSocket::CInternalSocket(){

	int nIP_TTL = 1;
	int err;

	DWORD bufsize;
	DWORD bFlag;

	wchar_t strDestMulti[] = _T("224.1.1.1"); // ��ַ�㲥��ַ��Χ�� 224 �� 239 ��
	u_short nDestPort = 6666;
	int addrlen = wcslen(strDestMulti) * 2;


	err = WSAStringToAddress ( strDestMulti, /* address string */
		AF_INET, /* address family */
		NULL, /* protocol info structure */
		(LPSOCKADDR)&stDestAddr, /* socket address string */
		&addrlen); /* length of socket structure */

	if(err)
		return;


	ASSERT(m_hSocket == INVALID_SOCKET);

	m_hSocket = WSASocket(PF_INET, SOCK_DGRAM, 0 , NULL, 0,
		WSA_FLAG_OVERLAPPED| WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF);
	
	if(m_hSocket == INVALID_SOCKET)
		return;

	//Create(6666, SOCK_DGRAM, FD_READ | FD_WRITE, theApp.GetBindAddress()/* strDestMulti thePrefs.GetBindAddrW()*/);

	bFlag = TRUE; // �����׽���Ϊ�����ö˿ڵ�ַ

	err = setsockopt(m_hSocket, /* socket */
		SOL_SOCKET, /* socket level */
		SO_REUSEADDR, /* socket option */
		(char *)&bFlag, /* option value */
		sizeof (bFlag)); /* size of value */

	if(err)
		return;
	

	if(AsyncSelect()){
		//Bind(6666, strDestMulti);
	}

	AttachHandle(m_hSocket, this, FALSE);

	err = WSAIoctl (m_hSocket, /* socket */
		SIO_MULTICAST_SCOPE, /* IP Time-To-Live */
		&nIP_TTL, /* input */
		sizeof (nIP_TTL), /* size */
		NULL, /* output */
		0, /* size */
		&bufsize, /* bytes returned */
		NULL, /* overlapped */
		NULL); /* completion routine */

	if(err)
		return;


	bFlag = FALSE;	//False = LOOPBACK

	err = WSAIoctl (m_hSocket, /* socket */
		SIO_MULTIPOINT_LOOPBACK, /* LoopBack on or off */
		&bFlag, /* input */
		sizeof (bFlag), /* size */
		NULL, /* output */
		0, /* size */
		&bufsize, /* bytes returned */
		NULL, /* overlapped */
		NULL); /* completion routine */

	if(err)
		return;


	stDestAddr.sin_family = PF_INET;
	err = WSAHtons( m_hSocket, /* socket */
		nDestPort, /* host order value */
		&(stDestAddr.sin_port)); /* network order value */

	if (err == SOCKET_ERROR)
		return;


	// ���뵽ָ����ַ�㲥�飬ָ��Ϊ��������������������
	// �� IP multicast �У����ص��׽�����������������׽�����������ͬ��
	m_hSocket2 = WSAJoinLeaf (m_hSocket, /* socket */
		(PSOCKADDR)&stDestAddr, /* multicast address */
		sizeof (stDestAddr), /* length of addr struct */
		NULL, /* caller data buffer */
		NULL, /* callee data buffer */
		NULL, /* socket QOS setting */
		NULL, /* socket group QOS */
		JL_BOTH); /* do both: send *and* receive */

	if (m_hSocket2 == INVALID_SOCKET)
		return;

	if (err)
		return;

}

//CInternalSocket::~CInternalSocket(){

	//closesocket(m_hSocket);
	//closesocket(m_hSocket2);

//}
void CInternalSocket::Broadcast(const uchar* filehash){


	WSABUF stWSABuf;
	CSafeMemFile packet;
	SOCKADDR_IN addr;

	DWORD bufsize;
	int err;
	int addrlen;
	
	addrlen = sizeof(addr);

	//uint32 server_ip = theApp.serverconnect->GetLocalIP();
	//uint16 server_udpport = theApp.serverconnect->GetLocalUDP();

	CAsyncSocket::GetSockName((SOCKADDR*)&addr, &addrlen);

	packet.WriteUInt8(OP_VC_BC_HEADER);
	packet.WriteUInt8(OP_BC_REQUESTSOURCE);

	packet.WriteHash16(filehash);
	packet.WriteUInt32((uint32)addr.sin_addr.s_addr);
	packet.WriteUInt16((uint16)addr.sin_port);

	//CKnownFile* partfile = NULL;
	//partfile = theApp.sharedfiles->GetFileByID(filehash);

	stWSABuf.buf = (char*)packet.GetBuffer();
	stWSABuf.len = (uint32)packet.GetLength();

	err = WSASendTo(m_hSocket, /* socket */
		&stWSABuf, /* output buffer structure */
		1, /* buffer count */
		&bufsize, /* number of bytes sent */
		0, /* flags */
		(struct sockaddr*)&stDestAddr, /* destination address */
		sizeof(struct sockaddr), /* size of addr structure */
		NULL, /* overlapped structure */
		NULL); /* overlapped callback function */

	if(err)
		return;
}

void CInternalSocket::Process(char* buffer, uint32 buffersize){

	CSafeMemFile req((const BYTE*)buffer,(UINT)buffersize);
	CSafeMemFile res;

	CKnownFile* file = NULL;
	CPartFile* partfile = NULL;
	uchar filehash[16];
	//SOCKADDR_IN addr,ownaddr;

	WSABUF stWSABuf;
	DWORD bufsize;

	int err;
	//int addrlen;
	uint8 opcode;
    
    if(theApp.emuledlg->IsRunning()){

        ASSERT(theApp.serverconnect);
        uint32 ip = theApp.serverconnect->GetLocalIP();
        uint16 port = thePrefs.GetPort();
        uint32 userid = theApp.serverconnect->GetClientID();

	    if(buffersize == 24){

		    if(req.ReadUInt8() != OP_VC_BC_HEADER)
				return;

		    opcode = req.ReadUInt8();
		    req.ReadHash16(filehash);

		    if(opcode == OP_BC_REQUESTSOURCE){

			    file = theApp.sharedfiles->GetFileByID(filehash);
			    if(file == NULL)
					return;

			    //CAsyncSocket::GetSockName((SOCKADDR*)&ownaddr, &addrlen);

			    res.WriteUInt8(OP_VC_BC_HEADER);
			    res.WriteUInt8(OP_BC_ANSWERSOURCE);
			    res.WriteHash16(filehash);

			    res.WriteUInt32(ip);
			    res.WriteUInt16(port);
                res.WriteUInt32(userid);

			    stWSABuf.buf = (char*)res.GetBuffer();
			    stWSABuf.len = (u_long)res.GetLength();
			    bufsize = (DWORD)res.GetLength();

			    err = WSASendTo(m_hSocket, /* socket */
				    &stWSABuf, /* output buffer structure */
				    1, /* buffer count */
				    &bufsize, /* number of bytes sent */
				    0, /* flags */
				    (struct sockaddr*)&stDestAddr, /* destination address */
				    sizeof(struct sockaddr), /* size of addr structure */
				    NULL, /* overlapped structure */
				    NULL); /* overlapped callback function */

			    if (err){
				    err = WSAGetLastError();
				    return;
			    }
		    }
        }

        if(buffersize == 28){

            if(req.ReadUInt8() != OP_VC_BC_HEADER)
				return;

            opcode = req.ReadUInt8();
            req.ReadHash16(filehash);

            if(opcode == OP_BC_ANSWERSOURCE){

                ip = req.ReadUInt32();
                port = req.ReadUInt16();
                userid = req.ReadUInt32();

                partfile = theApp.downloadqueue->GetFileByID(filehash);

                if(partfile){

                    CUpDownClient* toadd = new CUpDownClient(partfile, port, userid, 0, 0);
                    toadd->SetIP(ip);
                    theApp.downloadqueue->CheckAndAddSource(partfile, toadd);

                }
            }
        }
    }
}

void CInternalSocket::OnSend(int nErrorCode){

	printf("%d",nErrorCode);

}

void CInternalSocket::OnReceive(int nErrorCode){

#ifndef _ENABLE_LAN_TRANSFER
	return;
#endif

	printf("%d",nErrorCode);

	int err;
	int addrlen;
	DWORD dFlag;
	DWORD bufsize;

	WSABUF stWSABuf;
	char achInBuf[BUFSIZE];


	stWSABuf.buf = achInBuf;
	stWSABuf.len = BUFSIZE;

	bufsize = 0;
	dFlag = 0;
	addrlen = sizeof(stSrcAddr);

	err = WSARecvFrom (m_hSocket, /* socket */
		&stWSABuf, /* input buffer structure */
		1, /* buffer count */
		&bufsize, /* number of bytes recv'd */
		&dFlag, /* flags */
		(struct sockaddr *)&stSrcAddr, /* source address */
		&addrlen, /* size of addr structure */
		NULL, /* overlapped structure */
		NULL); /* overlapped callback function */

	if (err){
		err = WSAGetLastError();
		return;
	}

	Process(achInBuf,bufsize);

}