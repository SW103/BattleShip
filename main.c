/*
#include <amlib.h>
#include <agdraw.h>
#include <agesndmgr.h>
#include <agetool.h>
#include <agtransfer.h>
#include <vdpreg.h>
#include <stdlib.h>
*/
#include "import.h"
#include "export.h"
#include "battleShip.h"
#include "field.h"
#include "player.h"
#include "game.h"
#include "touch.h"

//extern int holdingIndex;
/*
struct Rect{
	int x,y,w,h;
};
*/

void drawNumberGraph(int number ,int x, int y, int size_x, int size_y , int order ,AGDrawBuffer* DBuf) {
	int i, n;
	int draw_x;
	int id[10] = {AG_CG_NUM_0,AG_CG_NUM_1,AG_CG_NUM_2,AG_CG_NUM_3,AG_CG_NUM_4,AG_CG_NUM_5,AG_CG_NUM_6,AG_CG_NUM_7,AG_CG_NUM_8,AG_CG_NUM_9};
	draw_x = x + (order-1)*size_x;

	for(i=0;i<order;i++) {
		n = number%10;
		agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
		ageTransferAAC( DBuf, id[n], 0, NULL, NULL );
		agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
		agDrawSPRITE( DBuf, 1, draw_x, y, draw_x+size_x, y+size_y );
		number /= 10;
		draw_x -= size_x;
	}
}

#ifdef __DSP_3_BUFF__
static volatile u32 VSyncFlag=0;
#endif
static volatile u32 _SystemVSyncCount=0;

static s32 ifnc_vsync(int type)
{
#ifdef __DSP_3_BUFF__
    VSyncFlag=1;
#endif
    _SystemVSyncCount++;
    return(1);
}

static volatile u32 DrawExecFlag=0;

static s32 ifnc_draw(int type)
{
    DrawExecFlag=0;
    return(0);
}

void  main( void )  {
	AGDrawBuffer DBuf;

	int i;
	int MyID,ID;

	//ゲームのモード変数
	enum GameMode gameMode = MODE_START;

	//キー入力の格納配列
	//int key_state[KEY_NUM];

	//フィールド
	struct Field field[2];

	//戦艦
	//struct BattleShip battleShip[5];

	//プレイヤー
	struct Player player[2];

	//タッチ
	struct Touch touch[2];

#ifdef __DSP_3_BUFF__
    static u8 uFBINDEX[3]={
        AG_FB_INDEX0,
        AG_FB_INDEX1,
        AG_Z_INDEX,
    };
    u32 uMSRDP;
    u32 uINDEX;
    u32 data;

    uMSRDP=0;
    uINDEX=0;
#endif

    agpDisableCpuInterrupts();
    aglInitialize();
    agpEnableCpuInterrupts();

    aglAddInterruptCallback(AG_INT_TYPE_VBLA,ifnc_vsync);

    aglAddInterruptCallback(AG_INT_TYPE_DRW,ifnc_draw);
    aglAddInterruptCallback(AG_INT_TYPE_DLE,ifnc_draw);
    aglAddInterruptCallback(AG_INT_TYPE_DLI,ifnc_draw);

#ifdef DEBUG
    _dprintf( "\n>> sample [PDevSync2] start.\n" );
#endif

    agPDevSyncInit( FB_WIDTH, FB_HEIGHT, &_SystemVSyncCount, 60);

	//タッチの初期化
	initTouch(touch);

	_dprintf("Start\n");
	MyID=(int)agPDevSyncGetMyID();
	//_dprintf("%d",MyID);

	while( 1 ) {
        agPDevSyncWait();
		//タッチの取得
		getTouch(touch);
		switch(gameMode){
			case MODE_START:			
				runStart(touch, player);
				drawStart(&DBuf);
				if(player[0].Sync==1 && player[1].Sync==1){
					gameMode=MODE_BATTLE;
					initTouch(touch);
					initField(field);
					initPlayer(player);	
				}
				break;
			case MODE_SET:
				runSet(touch, field, player);
				drawSet(&DBuf, field, player);
				break;
			case MODE_BATTLE:
				runBattle(touch, field, player);
				drawBattle(&DBuf, field, player);
				for(ID=0;ID<PLAYER_NUM;ID++){
					for(i=0;i<BATTLESHIP_NUM;i++){
						if(player[ID].battleShip[i].life==0){
							gameMode=MODE_END;
							player[ID].Result=-1;
						}else{
							gameMode=MODE_BATTLE;
							player[ID].Result=0;
							break;
						}

					}
				}
				break;
			case MODE_END:
				runEnd(touch, player);
				drawEnd(&DBuf, player);
				if(player[0].Sync==1 && player[1].Sync==1){
					gameMode=MODE_START;
					initPlayer(player);	
				}
				break;
			default:
				break;
		}
	
		//数字を描画する場所の白い四角
		//agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 255, 255 ) );
		//agDrawSETDBMODE( &DBuf, 0xff, 0, 0, 1 );
		//agDrawSPRITE( &DBuf, 0, 100-20, 100-20, 100+50*10+20, 100+90+20);
		//数字の描画
		//drawNumberGraph(holdingIndex, 100,100,50,90,10,&DBuf);

		//drawNumberGraph(i, 100,200,50,90,10,&DBuf);
			
		agDrawEODL( &DBuf );
		agTransferDrawDMA( &DBuf );
	
		aglWaitVSync();
		aglSwap();
	};
}
