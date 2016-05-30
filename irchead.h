#ifndef __IRCHEAD_H_INCLUDED__
#define __IRCHEAD_H_INCLUDED__
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdio>
#include <stdio.h>
#include <conio.h>
class Ircbot
{
	public:
		Ircbot(char * _nick, char *_oauth);
		virtual ~Ircbot();
		void startup();
		void servconn();
		void chanconn();
		void sendmsg(char *msg);
		void disconnect();
	private:
		SOCKET sock;
		char *nick, *oauth;
};

#endif
