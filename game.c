#include "game.h"

u32 DrawBuffer[ 4096*10 ];

struct HoldingObject hold;

void initGame()
{
	return;
}

void runSet(struct Touch* touch, struct Field* field, struct Player* player)
{
	int index = -1;
	int i, j;

	if(touch->count == 1){
		index = getTouchObject(touch/*, field*/, player, &hold);
		//_dprintf("index = %d \n", index);
		if( index >= 0/* && type == BATTLESHIP*/ ){
			//タッチされた戦艦を不可視にする
			player->battleShip[index].visible = 0;
			//戦艦をつかむ
			hold.shipIndex = index;
		}
	}else if(touch->count == -1 && hold.obj != NONE_OBJ){
		index = getReleaseObject(&i, &j, touch, field, player);
		//_dprintf("i = %d  \n", i);
		//_dprintf("j = %d  \n\n", j);
		if( index == 1 && placeable(touch, field, &hold) == 1 ){ // 盤上でリリースしたとき
			//放された戦艦の位置を変更する
			player->battleShip[hold.shipIndex].i = i - hold.d_i;
			player->battleShip[hold.shipIndex].j = j - hold.d_j;
		}

		//放された戦艦を可視にする
		player->battleShip[hold.shipIndex].visible = 1;
		//なにもつかんでいない
		hold.shipIndex = -1;
	}
}

void runBattle()
{
	return;
}


void drawSet(AGDrawBuffer* DBuf, struct Player* player)
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
int getTouchObject(struct Touch* touch/*, struct Field* field*/, struct Player* player, struct HoldingObject* hold)
{
	int x = touch->x;
	int y = touch->y;
	int i, j;
	int ship_index;

	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		hold->obj = NONE_OBJ;
		return -1;
	}

	// 範囲内のとき
	i = (x - FIELD_X)/CELL_SIZE;
	j = (y - FIELD_Y)/CELL_SIZE;

	// もし戦艦がいるのなら戦艦の番号を取得
	// もし戦艦がいないのなら -1 
	ship_index = getBattleShip(player, i, j);

	//戦艦がいないとき
	if(ship_index == -1){
		hold->obj = NONE_OBJ;
		return -1;
	}

	hold->d_i = i - player->battleShip[ship_index].i;
	hold->d_j = j - player->battleShip[ship_index].j;
	hold->battleShip = player->battleShip + ship_index;
	hold->obj = BATTLESHIP_OBJ;
	
	return ship_index;
}

// リリースした場所を取得
int getReleaseObject(int* i, int* j, struct Touch* touch, struct Field* field, struct Player* player)
{
	int x = touch->x;
	int y = touch->y;

	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		//*type = NULLTYPE;
		return -1;
	}

	// 範囲内のとき
	*i = (x - FIELD_X)/CELL_SIZE;
	*j = (y - FIELD_Y)/CELL_SIZE;
	
	return 1;
}


// リリースする位置に戦艦を配置できるかどうか
int placeable(struct Touch* touch, struct Field* field, struct HoldingObject* hold)
{
	int touch_i = touch->x;
	int touch_j = touch->y;
	int i, j, wid, len;
	
	//バトルシップの位置を取得
	getBattleShipPosition(hold->battleShip, &i, &j, &wid, &len);

	// タッチされた場所
	touch_i = (touch_i - FIELD_X)/CELL_SIZE;
	touch_j = (touch_j - FIELD_Y)/CELL_SIZE;

	//放した位置がフィールド内かどうかを調べる
	if(touch_i-hold->d_i < 0 || touch_i-hold->d_i+wid > FIELD_WIDTH_NUM
		|| touch_j-hold->d_j < 0 || touch_j-hold->d_j+len > FIELD_HEIGHT_NUM)
		return -1;
	return 1;
}
