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

void  main( void )  {
	AGDrawBuffer DBuf;

	int i;

	//ゲームのモード変数
	enum GameMode gameMode = MODE_SET;

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

	//初期化
	for(i=0;i<PLAYER_NUM;i++){
		initTouch(&touch[i]);
		initPlayer(&player[i]);
		initField(&field[i]);	
	}
	//holdのバトルシップに初期値を入れている
	initGame(&player[0]);

	//フィールドに初期値をいれる
	{
		int i,j,k;
		int ship_i,ship_j,w,l;
		for(i=0;i<5;i++){
			getBattleShipPosition(&player[0].battleShip[i], &ship_i, &ship_j, &w, &l);
			for(j=ship_i;j<ship_i+w;j++){
				for(k=ship_j;k<ship_j+l;k++){
					field[0].field[j][k] = 1;
				}
			}
		}
	}
	
	agpDisableCpuInterrupts();
	aglInitialize();
	agpEnableCpuInterrupts();

	//タッチの初期化
	agTouchInit(1024<<2,768<<2);

	while( 1 ) {

		//タッチの取得
		getTouch(&touch[0]);

		switch(gameMode){
			case MODE_SET:
				runSet(&touch[0], &field[0], &player[0]);
				drawSet(&DBuf, &field[0], &player[0]);
				break;
			case MODE_BATTLE:
				runBattle();
				drawBattle(&DBuf);
				break;
			default:
				break;
		}

	
		//回転ボタン
		agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 0, 0 ) );
		ageTransferAAC( &DBuf, AG_CG_KAITEN, 0, NULL, NULL );
		agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
		agDrawSPRITE( &DBuf, 1, s(300), s(600), s(300 + 200), s(600+100));
		//数字の描画
		//drawNumberGraph(holdingIndex, 100,100,50,90,10,&DBuf);
		
		drawNumberGraph(touch[0].count + 1, 100,200,50,90,10,&DBuf);
	
		//_dprintf("%d ", holdingIndex);
			
		agDrawEODL( &DBuf );
		agTransferDrawDMA( &DBuf );
	
		aglWaitVSync();
		aglSwap();
	};
}
