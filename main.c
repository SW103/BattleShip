#include <amlib.h>
#include <agdraw.h>
#include <agesndmgr.h>
#include <agetool.h>
#include <agtransfer.h>
#include <vdpreg.h>
#include <stdlib.h>

#include "export.h"

u32 DrawBuffer[ 4096*10 ];

#define KEY_NUM 8
#define FIELD_WIDTH_NUM 10
#define FIELD_HEIGHT_NUM 10
#define CELL_SIZE 50
#define FIELD_X 150
#define FIELD_Y 100
#define MAX_BATTLESHIP_HEIGHT_NUM 6
#define MAX_BATTLESHIP_WIDTH_NUM 2
#define s(x) (x<<2) 

enum Direction{
	LEFT,UP,RIGHT,DOWN,DIR_NUM
};

struct Rect{
	int x,y,w,h;
};

struct Field{
	int filed[FIELD_HEIGHT_NUM][FIELD_WIDTH_NUM];
};

struct BattleShip{
	int i,j;			//始点
	int len,wid;		//長さ、幅
	enum Direction dir;		//向いている方向
	int life;			//ライフ
	//被弾箇所の配列
	int bombed[MAX_BATTLESHIP_HEIGHT_NUM][MAX_BATTLESHIP_WIDTH_NUM];
};


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
	//sound系
	//SNDHANDLE handle;
	//u16 NowBgm = AS_SND_BGM_KOMACHI;
	//画像系
	AGDrawBuffer DBuf;
	//背景画像
	u16 fieldGraph = AG_CG_FIELD;
	//戦艦画像
	u16 battleShipGraph[DIR_NUM] = {AG_CG_SENKAN_LEFT,AG_CG_SENKAN_UP,AG_CG_SENKAN_RIGHT,AG_CG_SENKAN_DOWN};

	int i;

	//キー入力の格納配列
	int key_state[KEY_NUM];

	//戦艦
	struct BattleShip battleShip[5];

	agpDisableCpuInterrupts();
	aglInitialize();
	agpEnableCpuInterrupts();

	//戦艦の初期化
	for(i=0;i<5;i++){
		battleShip[i].i = i;
		battleShip[i].j = i;
		battleShip[i].len = 5;
		battleShip[i].wid = 1;
		battleShip[i].life = 1;
		battleShip[i].len = 5;
		battleShip[i].dir = LEFT;
	}
	battleShip[1].dir = RIGHT;
	battleShip[2].dir = UP;
	battleShip[3].dir = DOWN;

	while( 1 ) {
		//キー情報取得
		{
			int key = *((volatile unsigned short*)0xA9000002);

			for(i=0;i<KEY_NUM;i++){
				if((key|0xfffE)&0x0001){
					key_state[i] = 0;				
				}
				else{
					key_state[i] = 1;
				}
				key = key>>1;
			}
	
			//UP
			if(key_state[0]){
				
			}
			//DOWN
			if(key_state[1]){
				
			}
			//UPもDOWNも押されていない
			if(key_state[0]==0 && key_state[1]==0){
				
			}

			//RIGHT
			if(key_state[3]){
			
			}
			//LEFT
			if(key_state[2]){
			
			}
			//RIGHTもLEFTも押されていない
			if(key_state[2]==0 && key_state[3]==0){
			
			}

			//B
			if(key_state[5]){
			
			}

			//A
			if(key_state[4]){
			}
		}
		
		
		//描画
		{
			//Init
			agDrawBufferInit( &DBuf , DrawBuffer );
			agDrawSETDAVR( &DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
			agDrawSETDAVF( &DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

			//白背景
			agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 255, 255 ) );
			agDrawSETDBMODE( &DBuf, 0xff, 0, 0, 1 );
			agDrawSPRITE( &DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

			//フィールド
			agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 0, 0 ) );
			ageTransferAAC( &DBuf, fieldGraph, 0, NULL, NULL );
			agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
			agDrawSPRITE( &DBuf, 1, s(FIELD_X), s(FIELD_Y), s(FIELD_X+CELL_SIZE*FIELD_WIDTH_NUM), s(FIELD_Y+CELL_SIZE*FIELD_HEIGHT_NUM));

			//戦艦
			for(i=0;i<5;i++){
				agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 0, 0 ) );
				ageTransferAAC( &DBuf, battleShipGraph[battleShip[i].dir], 0, NULL, NULL );
				agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
				switch(battleShip[i].dir){
					case LEFT:
						agDrawSPRITE( &DBuf, 1, s(FIELD_X + battleShip[i].i*CELL_SIZE), s(FIELD_Y + battleShip[i].j*CELL_SIZE),
							s(FIELD_X + (battleShip[i].i + battleShip[i].len)*CELL_SIZE), s(FIELD_Y + (battleShip[i].j + battleShip[i].wid)*CELL_SIZE));
						break;
					case UP:
						agDrawSPRITE( &DBuf, 1, s(FIELD_X + battleShip[i].i*CELL_SIZE), s(FIELD_Y + battleShip[i].j*CELL_SIZE),
							s(FIELD_X + (battleShip[i].i + battleShip[i].wid)*CELL_SIZE), s(FIELD_Y + (battleShip[i].j + battleShip[i].len)*CELL_SIZE));
						break;
					case RIGHT:
						agDrawSPRITE( &DBuf, 1, s(FIELD_X + (battleShip[i].i - battleShip[i].len + 1)*CELL_SIZE), s(FIELD_Y + battleShip[i].j*CELL_SIZE),
							s(FIELD_X + (battleShip[i].i + 1)*CELL_SIZE), s(FIELD_Y + (battleShip[i].j + battleShip[i].wid)*CELL_SIZE));
						break;
					case DOWN:
						agDrawSPRITE( &DBuf, 1, s(FIELD_X + battleShip[i].i*CELL_SIZE), s(FIELD_Y + (battleShip[i].j - battleShip[i].len + 1 )*CELL_SIZE),
							s(FIELD_X + (battleShip[i].i + battleShip[i].wid)*CELL_SIZE), s(FIELD_Y + (battleShip[i].j + 1)*CELL_SIZE));
						break;
				}
				
			}
			
			//数字を描画する場所の白い四角
			agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 255, 255 ) );
			agDrawSETDBMODE( &DBuf, 0xff, 0, 0, 1 );
			agDrawSPRITE( &DBuf, 0, 100-20, 100-20, 100+50*10+20, 100+90+20);
			//数字の描画
			drawNumberGraph(20131120, 100,100,50,90,10,&DBuf);
			
			agDrawEODL( &DBuf );
			agTransferDrawDMA( &DBuf );
		};


		aglWaitVSync();
		aglSwap();
	};
}
