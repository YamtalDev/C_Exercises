#ifndef __UNIQUE_IDENTIFIER_H__
#define __UNIQUE_IDENTIFIER_H__

#include <sys/types.h>

typedef struct ilrd_uid
{
	size_t counter;
	time_t time_stamp;
	pid_t pid;

} ilrd_uid_t;

/* TC: O(1) Returns a uid else returns Bad uid */
ilrd_uid_t UIDCreate(void);

/* TC: O(1) Returns non valid uid*/
ilrd_uid_t UIDGetBad(void);

/* TC: O(1) Returns non zero if a uid1 equals to uid2 and 0 if not */
int UIDIsMatch(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif /* __UNIQUE_IDENTIFIER_H__ */
