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
#include <stdio.h>   /* printf, puts */
#include <assert.h>  /*   assert     */
#include <stddef.h>  /* NULL, size_t */
#include <time.h>    /*     time     */
#include <unistd.h>  /*     types    */

#include "unique_identifier.h"
void UIDCreateTest(void);
void UIDGetBadTest(void);
void UIDIsMatchTest(void);

/*****************************************************************************/
int main(void)
{
	UIDCreateTest();
	puts("\n UIDCreateTest() : passed.");
	UIDGetBadTest();
	puts("\n UIDGetBadTest() : passed.");
	UIDIsMatchTest();
	puts("\n UIDIsMatchTest() : passed.");
	return (0);
}
/*****************************************************************************/
void UIDCreateTest(void)
{
	pid_t pid = getpid();
	ilrd_uid_t uid1 = UIDCreate();
	ilrd_uid_t uid2 = UIDCreate();
	ilrd_uid_t uid3 = UIDCreate();
	ilrd_uid_t uid4 = UIDCreate();
	ilrd_uid_t uid5 = UIDCreate();
	ilrd_uid_t uid6 = UIDCreate();
	ilrd_uid_t uid7 = UIDCreate();
	assert(uid1.pid == pid);
	assert(uid1.counter == 0);
	assert(uid2.pid == pid);
	assert(uid2.counter == 1);
	assert(uid3.pid == pid);
	assert(uid3.counter == 2);
	assert(uid4.pid == pid);
	assert(uid4.counter == 3);
	assert(uid5.pid == pid);
	assert(uid5.counter == 4);
	assert(uid6.pid == pid);
	assert(uid6.counter == 5);
	assert(uid7.pid == pid);
	assert(uid7.counter == 6);
}
/*****************************************************************************/
void UIDGetBadTest(void)
{
	ilrd_uid_t bad = UIDGetBad();
	assert(bad.counter == 0);
	assert(bad.pid == 0);
	assert(bad.time_stamp == 0);
}
/*****************************************************************************/
void UIDIsMatchTest(void)
{
	ilrd_uid_t uid1 = UIDCreate();
	ilrd_uid_t uid2 = UIDCreate();
	assert(!UIDIsMatch(uid1, uid2));
	assert(UIDIsMatch(uid1, uid1));
}
/*****************************************************************************/
