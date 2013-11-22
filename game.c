#include "game.h"

u32 DrawBuffer[ 4096*10 ];

enum ObjectType holdingType;
int holdingIndex;

void initGame()
{
	return;
}

void runSet(struct Touch* touch, struct Field* field, struct Player* player)
{
	int index = -1;
	//int index;
	int i, j;
	enum ObjectType type;

	if(touch->count == 1){
		index = getTouchObject(&type, touch, field, player);
		if( index >= 0 && type == BATTLESHIP ){
			//タッチされた戦艦を不可視にする
			player->battleShip[index].visible = 0;
			//戦艦をつかむ
			holdingType = BATTLESHIP;
			holdingIndex = index;
		}

	}else if(touch->count == -1){
		index = getReleaseObject(&i, &j, touch, field, player);
		if( index >= 0 ){
			//放された戦艦の位置を変更する
			player->battleShip[holdingIndex].i = i;
			player->battleShip[holdingIndex].j = j;
			//放された戦艦を可視にする
			player->battleShip[holdingIndex].visible = 1;
			//なにもつかんでいない
			holdingType = NULLTYPE;
			holdingIndex = -1;
		}

	}
}

void runBattle()
{
	return;
}


void drawSet(AGDrawBuffer* DBuf, struct Field* field, struct Player* player)
{
	int i;

	//Init
	agDrawBufferInit( DBuf , DrawBuffer );
	agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
	agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//白背景
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//フィールド
	drawField( DBuf, field);

	//戦艦
	for(i=0;i<5;i++){
		drawBattleShip(DBuf, &(player->battleShip[i]));
	}
	

	/*
	//数字を描画する場所の白い四角
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 100-20, 100-20, 100+50*10+20, 100+90+20);
	//数字の描画
	drawNumberGraph(20131120, 100,100,50,90,10,DBuf);
	*/
	
}

void drawBattle(AGDrawBuffer* DBuf)
{
	return;
}




// タッチしたオブジェクトの種類を取得
int getTouchObject(enum ObjectType* type, struct Touch* touch, struct Field* field, struct Player* player)
{
	int x = touch->x;
	int y = touch->y;
	int i, j;
	int index;

	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		*type = NULLTYPE;
		return -1;
	}

	// 範囲内のとき
	i = (x - FIELD_X)/CELL_SIZE;
	j = (y - FIELD_Y)/CELL_SIZE;
	
	*type = BATTLESHIP;
	return getBattleShip(player, i, j);
}

// リリースした場所を取得
int getReleaseObject(int* i, int* j, struct Touch* touch, struct Field* field, struct Player* player)
{
	int x = touch->x;
	int y = touch->y;
	//int i, j;
	int index;

	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		//*type = NULLTYPE;
		return -1;
	}

	// 範囲内のとき
	*i = (x - FIELD_X)/CELL_SIZE;
	*j = (y - FIELD_Y)/CELL_SIZE;
	
	//*type = BATTLESHIP;
	return getBattleShip(player, *i, *j);
}