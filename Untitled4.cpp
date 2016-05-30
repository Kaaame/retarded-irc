#include "irchead.h"
#define buf 120
//source file for class

Ircbot::Ircbot(char * _nick, char * _oauth)
{
	char *nick = _nick;
	char *oauth = _oauth;
}
Ircbot::~Ircbot()
{
	WSACleanup();
}

void Ircbot::startup()
{
	WSADATA wsaData;
	int iRes = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iRes != 0)
	{
		printf("doesnt support NT something something");
	}
	//SOCKET sock;
	
	struct addrinfo hints, *result;
	memset(&hints,'\0',sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	iRes = getaddrinfo("irc.twitch.tv", "6667", &hints, &result);//changed from irc.chat.twitch.tv
	if (iRes != 0)
	{
		printf("getaddrinfo failed");
		WSACleanup();
	}
	sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(sock == SOCKET_ERROR)
	{
		printf("error creating socket");
		WSACleanup();
	}
	iRes = connect(sock, result->ai_addr, result->ai_addrlen);
	if (iRes!=0)
	{
		printf("err:%s", WSAGetLastError());
		WSACleanup();
	}
	freeaddrinfo(result);	
}

void Ircbot::servconn()//DIES HERE
{
	int sentbytes, recvbytes;
	char sendmsg[buf], recvbuf[buf];
	memset(sendmsg, '\0', buf);
	strcpy(sendmsg, "PASS oauth:d1fiqkbzr3dh9l1c9m3jpsdmlshhdt\r\n");
	sentbytes = send(sock, sendmsg, strlen(sendmsg), 0);
	memset(sendmsg, '\0', buf);
	strcpy(sendmsg, "NICK strinnity212\r\n");
	sentbytes = send(sock, sendmsg, strlen(sendmsg), 0);
	memset(sendmsg, '\0', buf);
	strcpy(sendmsg, "USER strinnity212 irc.twitch.tv bla :strinnity212\r\n");
	sentbytes = send(sock, sendmsg, strlen(sendmsg), 0);
	memset(sendmsg, '\0', buf);
	strcpy(sendmsg, "PRIVMSG nickserv :identify strinnity212 oauth:d1fiqkbzr3dh9l1c9m3jpsdmlshhdt\r\n");
	sentbytes = send(sock, sendmsg, strlen(sendmsg), 0);
	memset(sendmsg, '\0', buf);
	strcpy(sendmsg, "JOIN #archonthewizard\r\n");
	sentbytes = send(sock, sendmsg, strlen(sendmsg), 0);
	memset(sendmsg, '\0', buf);
	/*recvbytes = recv(sock, recvbuf, buf, MSG_WAITALL);
	do
	{
		for(int i=0;i<=recvbytes;i++)
		{
			printf("%c", recvbuf[i]);
		}
		recvbytes = -1;
	}while(recvbuf[recvbytes]!='\0');
	if (recvbytes < 0)
	{
		printf("didnt connect to serv");
		WSACleanup();
	}*/
}
void Ircbot::chanconn()//optional change of channel, not included in tests
{
	int sentbytes, recvbytes;
	char sendmsg[buf], recvbuf[buf];
	memset(sendmsg, '\0', buf);
	//strcpy(sendmsg, "JOIN #archonthewizard");
	//sentbytes = send(sock, sendmsg, strlen(sendmsg), 0);
	recvbytes = recv(sock, recvbuf, buf, MSG_WAITALL);
	Sleep(10000);
	if (recvbytes < 0)
	{
		printf("couldnt connect to channel");
	}
	do
	{
		for(int i=0;i<=recvbytes;i++)
		{
			printf("%c", recvbuf[i]);
		}
		recvbytes = -1;
	}while(recvbuf[recvbytes]!='\0');
}
void Ircbot::sendmsg(char *msg)
{
	int sentbytes;
	char msgbuff[buf];
	strcpy(msgbuff, "PRIVMSG #archonthewizard :");
	strcat(msgbuff, msg);
	sentbytes = send(sock, msgbuff, strlen(msgbuff), 0);
}
void Ircbot::disconnect()
{
	int sentbytes;
	char msgbuff[buf];
	strcpy(msgbuff, "PART #strinnity121");
	sentbytes = send(sock, msgbuff, strlen(msgbuff), 0); 
}
