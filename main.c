/*
#include <amlib.h>
#include <agdraw.h>
#include <agesndmgr.h>
#include <agetool.h>
#include <agtransfer.h>
#include <vdpreg.h>
#include <stdlib.h>
*/
//#include "import.h"
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
	int id[10] = {AG_CG_NUM_0_0,AG_CG_NUM_1_0,AG_CG_NUM_2_0,AG_CG_NUM_3_0,AG_CG_NUM_4_0,AG_CG_NUM_5_0,AG_CG_NUM_6_0,AG_CG_NUM_7_0,AG_CG_NUM_8_0,AG_CG_NUM_9_0};
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

	int i, ship_num;
	int MyID,ID,turnID;

	//ゲームのモード変数
	enum GameMode gameMode = MODE_START;

	//キー入力の格納配列
	//int key_state[KEY_NUM];

	//フィールド
	struct Field field[PLAYER_NUM];

	//戦艦
	//struct BattleShip battleShip[5];

	//プレイヤー
	struct Player player[PLAYER_NUM];

	//タッチ
	struct Touch touch[PLAYER_NUM];

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

	//タッチの初期化
	agTouchInit(1024<<2,768<<2);

#ifdef DEBUG
    _dprintf( "\n>> sample [PDevSync2] start.\n" );
#endif


    agPDevSyncInit( FB_WIDTH, FB_HEIGHT, &_SystemVSyncCount, 60);

    initTouch(touch);
    _dprintf("Start\n");
    MyID=(int)agPDevSyncGetMyID();

	while( 1 ) {
	agPDevSyncWait();

		//タッチの取得
		getTouch(touch);

		switch(gameMode){
			case MODE_START:                        
                runStart(touch, player);
                drawStart(&DBuf);
                if(player[0].Sync==1 && player[1].Sync==1){
                	    initField(field);
    					initPlayer(player);
    					turnID=0;
                		player[0].Sync = 0;
                		player[1].Sync = 0;
                        gameMode=MODE_SET;
                }
                break;
			case MODE_SET:
				runSet(touch, field, player);
				drawSet(&DBuf, field, player, touch);
				if(player[0].Sync==2 && player[1].Sync==2){
                		player[0].Sync = 0;
                		player[1].Sync = 0;
                        gameMode=MODE_TURNBATTLE;
                }
				/*
				if(result==1){
					gameMode = MODE_SET_OVERLAP;
				}else if(result==2){
					gameMode = MODE_SET_WAIT;
				}*/
				break;
			case MODE_BATTLE:
				runBattle(touch, field, player);
				drawBattle(&DBuf, field, player);
				for(ID=0;ID<PLAYER_NUM;ID++){
					ship_num=BATTLESHIP_NUM;
					for(i=0;i<BATTLESHIP_NUM;i++){
						if(player[ID].battleShip[i].life==0){
							ship_num += -1;
						}
					}
					if(ship_num==0){
						player[ID].Result=-1;
						gameMode=MODE_END;
					}
				}
				break;
			case MODE_TURNBATTLE:
				runTurnBattle(touch, field, player, &turnID);
				drawBattle(&DBuf, field, player);
				for(ID=0;ID<PLAYER_NUM;ID++){
					ship_num=BATTLESHIP_NUM;
					for(i=0;i<BATTLESHIP_NUM;i++){
						if(player[ID].battleShip[i].life==0){
							ship_num += -1;
						}
					}
					if(ship_num==0){
						player[ID].Result=-1;
						gameMode=MODE_END;
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
