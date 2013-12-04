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

//Brunch Matsushita

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

void  main( void )  {
	AGDrawBuffer DBuf;

	int i;

	//ゲームのモード変数
	enum GameMode gameMode = MODE_SET;

	//キー入力の格納配列
	//int key_state[KEY_NUM];

	//フィールド
	struct Field field;

	//戦艦
	//struct BattleShip battleShip[5];

	//プレイヤー
	struct Player player;

	//タッチ
	struct Touch touch;

	//
	initTouch(&touch);
	initPlayer(&player);

	agpDisableCpuInterrupts();
	aglInitialize();
	agpEnableCpuInterrupts();

	//タッチの初期化
	agTouchInit(1024<<2,768<<2);

	while( 1 ) {

		//タッチの取得
		getTouch(&touch);

		switch(gameMode){
			case MODE_SET:
				runSet(&touch, &field, &player);
				drawSet(&DBuf, &field, &player);
				break;
			case MODE_BATTLE:
				runBattle();
				drawBattle(&DBuf);
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
		
		drawNumberGraph(touch.count + 1, 100,200,50,90,10,&DBuf);
	
		//_dprintf("%d ", holdingIndex);
			
		agDrawEODL( &DBuf );
		agTransferDrawDMA( &DBuf );
	
		aglWaitVSync();
		aglSwap();
	};
}
