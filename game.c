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
	enum ObjectType type;

	if(touch->count == 1){
		index = getTouchObject(&type, touch, field, player, &hold);
		//_dprintf("index = %d \n", index);
		if( index >= 0/* && type == BATTLESHIP*/ ){
			//タッチされた戦艦を不可視にする
			player->battleShip[index].visible = 0;
			//戦艦をつかむ
			hold.type = BATTLESHIP;
			hold.shipIndex = index;
		}

	}else if(touch->count == -1){
		index = getReleaseObject(&i, &j, touch, field, player);
		//_dprintf("i = %d  \n", i);
		//_dprintf("j = %d  \n\n", j);
		if( index >= 0 ){ // 盤上でリリースしたとき
			//放された戦艦の位置を変更する
			player->battleShip[hold.shipIndex].i = i - hold.d_i;
			player->battleShip[hold.shipIndex].j = j - hold.d_j;
		}
		//放された戦艦を可視にする
		player->battleShip[hold.shipIndex].visible = 1;
		//なにもつかんでいない
		hold.type = NULLTYPE;
		hold.shipIndex = -1;
	}
}

void runBattle(struct Touch* touch, struct Field* field, struct Player* player)
{
	int i,x,y;

	//攻撃ボタンが押され、かつマスが選択されていたら攻撃を行う。
	if( (touch->x >= ATTACK_BUTTON_X) 
		&& (touch->x < ATTACK_BUTTON_X+ATTACK_BUTTON_W) 
		&& (touch->y >= ATTACK_BUTTON_Y) 
		&& (touch->y < ATTACK_BUTTON_Y+ATTACK_BUTTON_H) ){
		if(field->selected!=-1){
			_dprintf("%d ", field->selected);
			if(getBattleShip(player, field->selected%10, field->selected/10, &hold ) != -1){
				field->field[field->selected/10][field->selected%10]=HIT;


			}else{
				field->field[field->selected/10][field->selected%10]=MISS;			
			}
		}
		field->selected=-1;	
	}


	//フィールドが押された時の反応。
	if( (touch->x >= FIELD_X) 
	&& (touch->y >= FIELD_Y) 
	&& (touch->x < FIELD_X+CELL_SIZE*FIELD_WIDTH_NUM)
	&& (touch->y < FIELD_Y+CELL_SIZE*FIELD_HEIGHT_NUM) ){

		x = (touch->x - FIELD_X)/CELL_SIZE;
		y = (touch->y - FIELD_Y)/CELL_SIZE;

		if( field->field[y][x]==UNSELECTED ){
			if(field->selected != -1)
				field->field[field->selected/10][field->selected%10]=UNSELECTED;
			field->selected=x+y*FIELD_WIDTH_NUM;
			field->field[y][x]=SELECTED;
		}else if( field->field[y][x]==HIT || field->field[y][x]==MISS ){
			if(field->selected != -1)
				field->field[field->selected/10][field->selected%10]=UNSELECTED;
				field->selected = -1;
		}
	}else{
		field->field[field->selected/10][field->selected%10]=UNSELECTED;
		field->selected=-1;	
	}

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
	drawField( DBuf, field, s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));

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

void drawBattle(AGDrawBuffer* DBuf, struct Field* field, struct Player* player)
{
	int i,w,h;

	//Init
	agDrawBufferInit( DBuf , DrawBuffer );
	agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
	agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//白背景
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//敵のフィールド
	drawField( DBuf, field, s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));


	//自分のフィールド
	drawField( DBuf, field, s(700), s(125), s(30));


	for(i=0;i<5;i++){
		drawBattleShip(DBuf, &(player->battleShip[i]));
	}

	//攻撃ボタン
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, AG_CG_ATTACK, 0, &w, &h );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, s(ATTACK_BUTTON_X), s(ATTACK_BUTTON_Y), s(ATTACK_BUTTON_X)+s(ATTACK_BUTTON_W), s(ATTACK_BUTTON_Y)+s(ATTACK_BUTTON_H) );	
}





// タッチしたオブジェクトの種類を取得
int getTouchObject(enum ObjectType* type, struct Touch* touch, struct Field* field, struct Player* player, struct HoldingObject* hold)
{
	int x = touch->x;
	int y = touch->y;
	int i, j;

	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		*type = NULLTYPE;
		return -1;
	}

	// 範囲内のとき
	i = (x - FIELD_X)/CELL_SIZE;
	j = (y - FIELD_Y)/CELL_SIZE;
	
	*type = BATTLESHIP;
	return getBattleShip(player, i, j, hold);
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
int placeable(int i, int j, struct Player* player, struct HoldingObject* hold)
{


	
}