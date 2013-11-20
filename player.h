#ifndef __TASK_PLAYER_H__
#define __TASK_PLAYER_H__

#include <agtypes.h>

struct PlayerData {
	u8 direction;
	u8 count;
};

void InitTaskPlayer( struct TaskData* pTask );

#endif // __TASK_H__
