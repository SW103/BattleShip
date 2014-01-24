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
#include "effect.h"


#define DSPB_IDX0  10
#define DSPB_IDX1  11

u32 DrawBuffer[ 4096*10 ];

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

AGESoundManagerData SndMgrData;

void  main( void )  {
	AGDrawBuffer DBuf;
	//AGDrawBuffer *buf = &DBuf;

	s32 handle;

	int i, ship_num;
	int MyID,ID,turnID,battlemode;

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

	struct Effect title;
	struct Effect titleB;	
	struct Effect noise;
	struct Effect ocean;

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

	ageSndMgrInit( &SndMgrData , AGE_SOUND_ROM_OFFSET );

	//	ƒ}ƒXƒ^[ƒ{ƒŠƒ…[ƒ€Ý’è
	for( i=0 ; i<AG_SND_MAX_MASTERVOLUME ; i++ ) {
		ageSndMgrSetMasterVolume( i , 0x94 );
	};

	//	ƒ`ƒƒƒ“ƒlƒ‹ƒ{ƒŠƒ…[ƒ€Ý’è
	for( i=0 ; i<AG_SND_MAX_CHANNEL ; i++ ) {
		ageSndMgrSetChannelVolume( i , 0xc0 );
	};


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
    initEffect(&title);
    initEffect(&titleB);
    initEffect(&ocean);
    initEffect(&noise);
    _dprintf("Start\n");
    title.Name=AG_RP_BATTLESHIP_TITLE;
    title.LastFrame=99;
    titleB.Name=AG_RP_BATTLESHIP_TITLE;
    titleB.LastFrame=99;
    ocean.Name=AG_RP_OCEAN;
    ocean.LastFrame=99;
    noise.Name=AG_RP_NOISE;
    noise.LastFrame=9;

    MyID=(int)agPDevSyncGetMyID();

	// 表示回路Bのフレームバッファを確保.
	aglSetFBIndex(DSPB_IDX0, AG_VRAM_SIZE / 4 - FB_SIZE * 5, FB_WIDTH, 1);
	aglSetFBIndex(DSPB_IDX1, AG_VRAM_SIZE / 4 - FB_SIZE * 4, FB_WIDTH, 1);

	// 表示回路Bのフレームバッファのインデックス値.
	AG4REG.DSPBINDEX.INDEX0 = DSPB_IDX0;
	AG4REG.DSPBINDEX.INDEX1 = DSPB_IDX1;

	// 表示回路Bのタイミング設定をAと同様にする.
	AG4REGL.DSPBMODE   = AG_PARAM_DSPMODE;
	AG4REGL.DSPBDTH    = AG_PARAM_DSPDTH;
	AG4REGL.DSPBRDP    = AG_PARAM_DSPRDP;
	AG4REGL.DSPBHPRM0  = AG_PARAM_DSPHPRM0;
	AG4REGL.DSPBVPRM0  = AG_PARAM_DSPVPRM0;
	AG4REGL.DSPBHPRM1  = AG_PARAM_DSPHPRM1;
	AG4REGL.DSPBVPRM1  = AG_PARAM_DSPVPRM1;
	AG4REGL.DSPBSCALE1 = AG_PARAM_DSPSCALE1;
	AG4REGL.DSPBSCALE2 = AG_PARAM_DSPSCALE2;
	AG4REGL.DSPBSIZE0  = AG_PARAM_DSPSIZE;
	AG4REGL.DSPBSCLR   = AG_PARAM_DSPSCLR;
	AG4REGL.DSPBSPOS   = AG_PARAM_DSPSPOS;
	AG4REGL.DSPBSIZE2  = AG_PARAM_DSPSIZE2;

	// DotCLKBのPLL設定をDotCLKAと同様にする.
	AG4REGL.PLLDOTB = AG_PARAM_PLLDOTA;
	AG4REG.MACROCFG.PLLDB = 1;

	// 出力設定.
	AG4REG.DSPLVDS.LNKSRC =
		(0 << 1) |                  // lvds link1 source 0:A 1:B
    	(1 << 0) ;                  // lvds link2 source 0:A 1:B
	AG4REG.DSPLVDS.FMT =
    	(1 << 1) |                  // lvds link1 format
    	(1 << 0) ;                  // lvds link2 format
	AG4REG.CMOSRGBCFG.SELC = 1;   // rgb source 0:A 1:B
	AG4REG.DSPPINOUT.LVDS1 = 1;   // lvds1 output 0:off 1:on
	AG4REG.DSPPINOUT.LVDS2 = 1;   // lvds2 output 0:off 1:on
	AG4REG.DSPPINOUT.RGB = 1;     // rgb   output 0:off 1:on

	// 表示回路Bを有効にする.
	aglDispOnB(1);


	while( 1 ) {

		agPDevSyncWait();
		ageSndMgrRun();

		//タッチの取得
		getTouch(touch);

    	//Init
   		agDrawBufferInit( &DBuf , DrawBuffer );


		//表示回路A
    	agDrawSETDAVR( &DBuf , 0 , 0 , aglGetDrawFrameA() , 0 , 0 );
    	agDrawSETDAVF( &DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

        drawStart(&DBuf,&titleB);
        countEffect( &titleB );    	


		//表示回路B
    	agDrawSETDAVR( &DBuf , 0 , 0 , aglGetDrawFrameB() , 0 , 0 );
    	agDrawSETDAVF( &DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

		switch(gameMode){
			case MODE_START:                        
                runStart(touch, player);
                drawStart(&DBuf,&title);
                countEffect( &title );
                if(player[0].Sync==1 || player[1].Sync==1){
                	    initField(field);
    					initPlayer(player);
    					turnID=0;
                		player[0].Sync = 0;
                		player[1].Sync = 0;
                        gameMode=MODE_SELECT;
						/*
						handle = ageSndMgrAlloc( AS_SND_SAKUSENKAIGI , 0 , 1 , AGE_SNDMGR_PANMODE_LR12 , 0 );
						ageSndMgrPlay( handle );
						ageSndMgrSetVolume( handle , 0xa0 );
						ageSndMgrSetPanMode( handle , 0 );
						ageSndMgrSetPan( handle , 0x8080 );
						*/
                }
                break;
            case MODE_SELECT:
            	runSelect(touch, player, &battlemode);
            	drawSelect(&DBuf, player);
                if(player[0].Sync==1 || player[1].Sync==1){
                	    initField(field);
    					initPlayer(player);
    					turnID=0;
                		player[0].Sync = 0;
                		player[1].Sync = 0;
                        gameMode=MODE_SET;
                        //ボイス：戦艦を配置してね
                        if(MyID==0)
       						ageSndMgrPlayOneshot( AS_SND_A03 , 0 , 0x80 , AGE_SNDMGR_PANMODE_LR12 , 0x80 , 0 );
                        if(MyID==1)
       						ageSndMgrPlayOneshot( AS_SND_B03 , 0 , 0x80 , AGE_SNDMGR_PANMODE_LR12 , 0x80 , 0 );
                }
                break;
			case MODE_SET:
				runSet(touch, field, player);
				drawSet(&DBuf, field, player, touch, &ocean);
				countEffect(&ocean);
				if(player[0].Sync==2 && player[1].Sync==2){
                		player[0].Sync = 0;
                		player[1].Sync = 0;
                        gameMode=battlemode;

						/*
                        ageSndMgrRelease( handle );
						handle = ageSndMgrAlloc( AS_SND_HISHOU , 0 , 1 , AGE_SNDMGR_PANMODE_LR12 , 0 );
						ageSndMgrPlay( handle );
						ageSndMgrSetVolume( handle , 0xa0 );
						ageSndMgrSetPanMode( handle , 0 );
						ageSndMgrSetPan( handle , 0x8080 );     
						*/
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
				drawBattle(&DBuf, field, player, &ocean);
				countEffect(&ocean);
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
				drawBattle(&DBuf, field, player, &ocean);
				countEffect(&ocean);
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
					initEffect(&title);
					initEffect(&ocean);
					initEffect(&noise);
					ageSndMgrRelease( handle );
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
		aglSwapA();
		aglSwapB();
	};
}
