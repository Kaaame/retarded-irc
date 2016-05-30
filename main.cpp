#include "irchead.h"

int main()
{
	Ircbot asd("asd", "asd");
	asd.startup();
	asd.servconn();
	asd.chanconn();
	asd.chanconn();
	asd.chanconn();
	asd.chanconn();
	asd.chanconn();
	asd.chanconn();
	asd.chanconn();
	asd.sendmsg("wot m8");
	getch();
}
