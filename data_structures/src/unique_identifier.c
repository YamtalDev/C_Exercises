/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Ishay Zilberman           ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date : 02.04.2023                   ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <stddef.h> /* NULL, size_t */
#include <time.h>   /*     time     */
#include <unistd.h> /*     types    */

#include "unique_identifier.h"

static size_t count = 0;

/*****************************************************************************/
ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid = {0};
	time_t now = 0;

	if((time_t)-1 == time(&now)){return UIDGetBad();}

	uid.time_stamp = now;
	uid.counter = ++count;
	uid.pid = getpid();

	return uid;
}
/*****************************************************************************/ 
ilrd_uid_t UIDGetBad(void)
{
	ilrd_uid_t Bad = {0};
	Bad.time_stamp = 0;
	Bad.counter = 0;
	Bad.pid = 0;
	return Bad;
}
/*****************************************************************************/ 
int UIDIsMatch(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.time_stamp == uid2.time_stamp && uid1.counter == uid2.counter
	&& uid1.pid == uid2.pid);
}
/*****************************************************************************/ 
