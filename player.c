#include <amlib.h>
#include <agdraw.h>
#include <agesndmgr.h>
#include "task.h"
#include "pad.h"
#include "mode.h"
#include "export.h"
#include "global.h"

/******************************************************************/
/*                                player                          */
/******************************************************************/
static s32 CalcPlayer( struct TaskData* pTask , u32 Flag ) {
	pTask->Data.player.direction = 0;

	if( PadLvl()&PAD_UP    ) pTask->y -= 6;
	if( PadLvl()&PAD_DOWN  ) pTask->y += 6;
	if( PadLvl()&PAD_LEFT  ) {
		pTask->Data.player.direction = 1;
		pTask->x -= 6;
	};
	if( PadLvl()&PAD_RIGHT ) {
		pTask->Data.player.direction = 2;
		pTask->x += 6;
	};

	if( PadTrg()&PAD_B || PadRpt()&PAD_X ) {
		struct TaskData* pBulletTask;

		ageSndMgrPlayOneshot( AS_SND_TAMAHASSHA1 , 0 , 0x80 , AGE_SNDMGR_PANMODE_LR12 , 0x80 , 0 );

		pBulletTask = AllocTask();
		InitTaskPBullet( pBulletTask , pTask->x<<2 , (pTask->y - 64)<<2 , AG_CG_BULLET_A_CIRCLE + (rand()%4) , 0 , -100 , 0 , 0 );
		AddlLink( pBulletTask , DISP_LEVEL_PBULLET );
	};

	g_PlayerX = pTask->x <<2;
	g_PlayerY = pTask->y <<2;

	pTask->Data.player.count++;


	{
		struct TaskData* pBTask;

		pBTask = GetDispLink(DISP_LEVEL_EXPLOSION);
		while(pBTask != NULL && pBTask->flag != TASK_FLAG_DESTROY){
			if((pBTask->x - g_PlayerX) * (pBTask->x - g_PlayerX) + (pBTask->y - g_PlayerY) * (pBTask->y - g_PlayerY) < 200*200){
				g_PlayerStock--;
				if(g_PlayerStock == 0){
					GotoMode(MODE_TITLE);
				};
				pBTask->flag = TASK_FLAG_DESTROY;
				pBTask->visible = 0;
				break;
			}
			pBTask = pBTask->Next;
		}


	}

	return( 0 );
}

static s32 DrawPlayer( struct TaskData* pTask , AGDrawBuffer* pDBuf ) {
	int w, h;
	int pat;

	agPictureSetBlendMode( pDBuf , 0 , 0xff , 0 , 0 , 2 , 1 );

	pat = (pTask->Data.player.count>>2) & 1;

	if( pTask->Data.player.direction == 1 ) {
		ageTransferAAC( pDBuf, AG_CG_SHOOTING_PLAYER_LEFT_DEFAULT_0 + pat, 0, &w, &h );
	}
	else if( pTask->Data.player.direction == 2 ) {
		ageTransferAAC( pDBuf, AG_CG_SHOOTING_PLAYER_RIGHT_DEFAULT_0 + pat, 0, &w, &h );
	}
	else {		//@direction == 0
		ageTransferAAC( pDBuf, AG_CG_SHOOTING_PLAYER_TOP_DEFAULT_0 + pat, 0, &w, &h );
	};

	agDrawSPRITE( pDBuf, 1 , (pTask->x-w/2)<<2, (pTask->y-h/2)<<2 , (pTask->x+w/2)<<2, (pTask->y+h/2)<<2 );

	return( 0 );
}

void InitTaskPlayer( struct TaskData* pTask ) {
	memset( pTask , 0 , sizeof( *pTask ) );

	pTask->type = TASK_PLAYER;
	pTask->visible = 1;
	pTask->x = AGE_FB_WIDTH/2;
	pTask->y = 594;
	pTask->Calc = CalcPlayer;
	pTask->Draw = DrawPlayer;
	pTask->Data.player.direction = 0;
	pTask->Data.player.count = 0;
}
