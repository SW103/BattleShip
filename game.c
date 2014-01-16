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
		//drawBattleShip(DBuf, &(player->battleShip[i]));
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

void runBattle(struct Touch* touch, struct Field* field, struct Player* player)
{
	int i,x,y;
	int w,h;
	int index,ID,EnID;



	for(ID=0;ID<PLAYER_NUM;ID++){
		if(ID==0){
			EnID=1;
		}else{
			EnID=0;
		}		

		//攻撃ボタンが押され、かつマスが選択されていたら攻撃を行う。
		if( (touch[ID].x >= ATTACK_BUTTON_X) 
			&& (touch[ID].x < ATTACK_BUTTON_X+ATTACK_BUTTON_W) 
			&& (touch[ID].y >= ATTACK_BUTTON_Y) 
			&& (touch[ID].y < ATTACK_BUTTON_Y+ATTACK_BUTTON_H) ){
			if(field[EnID].selected!=-1){

				index = getBattleShip(&player[EnID], field[EnID].selected%10, field[EnID].selected/10, &hold );
				if(index != -1){

					field[EnID].field[field[EnID].selected/10][field[EnID].selected%10]=HIT;
					for(i=0;i<player[EnID].battleShip[index].len;i++){
						if(player[EnID].battleShip[index].bombed[i] == field[EnID].selected){
							player[EnID].battleShip[index].bombed[i] = -1;
							player[EnID].battleShip[index].life += -1;
						}
					}
				}else{
					field[EnID].field[field[EnID].selected/10][field[EnID].selected%10]=MISS;			
				}
			}
			field[EnID].selected=-1;	
		}

		//フィールドが押された時の。
		if( (touch[ID].x >= FIELD_X) 
			&& (touch[ID].y >= FIELD_Y) 
			&& (touch[ID].x < FIELD_X+CELL_SIZE*FIELD_WIDTH_NUM)
			&& (touch[ID].y < FIELD_Y+CELL_SIZE*FIELD_HEIGHT_NUM) ){

			x = (touch[ID].x - FIELD_X)/CELL_SIZE;
			y = (touch[ID].y - FIELD_Y)/CELL_SIZE;

			if( field[EnID].field[y][x]==UNSELECTED ){
		
				for(h=0; h<FIELD_HEIGHT_NUM; h++){
					for(w=0; w<FIELD_WIDTH_NUM; w++){
						if(field[EnID].field[h][w]==SELECTED){
							field[EnID].field[h][w]=UNSELECTED;	
						}
					}
				}

			field[EnID].selected=x+y*FIELD_WIDTH_NUM;
			field[EnID].field[y][x]=SELECTED;
			}else if( field[EnID].field[y][x]==HIT || field[EnID].field[y][x]==MISS ){
				if(field[EnID].selected != -1){
					field[EnID].field[field[EnID].selected/10][field[EnID].selected%10]=UNSELECTED;
					field[EnID].selected = -1;
				}
			}
		}else{
			field[EnID].field[field[EnID].selected/10][field[EnID].selected%10]=UNSELECTED;
			field[EnID].selected=-1;	
		}
	}
}

void drawBattle(AGDrawBuffer* DBuf, struct Field* field, struct Player* player)
{
	int i,w,h,MyID,EnID;
	int x,y;

	MyID=(int)agPDevSyncGetMyID();
	if(MyID==0){
		EnID=1;
	}else{
		EnID=0;
	}

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
	drawFieldColor( DBuf, &field[EnID], s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));

	for(i=0;i<5;i++){
		if(player[EnID].battleShip[i].life == 0)
			drawBattleShip( DBuf, &(player[EnID].battleShip[i]), s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));
	}

	//自分のフィールド
	drawField( DBuf, field, s(700), s(125), s(30));
	drawFieldColor( DBuf, &field[MyID], s(700), s(125), s(30));

	for(i=0;i<5;i++){
		drawBattleShip( DBuf, &(player[MyID].battleShip[i]), s(700), s(125), s(30));
	}

	//攻撃ボタン
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, AG_CG_ATTACK, 0, &w, &h );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, s(ATTACK_BUTTON_X), s(ATTACK_BUTTON_Y), s(ATTACK_BUTTON_X)+s(ATTACK_BUTTON_W), s(ATTACK_BUTTON_Y)+s(ATTACK_BUTTON_H) );	
}


void runStart(struct Touch* touch, struct Player* player)
{
	int ID;
	
	for(ID=0; ID<PLAYER_NUM; ID++){
		if(touch[ID].stat==1){
			player[ID].Sync=1;
		}
	}
}

void drawStart(AGDrawBuffer* DBuf)
{
	int w,h;

	//Init
	agDrawBufferInit( DBuf , DrawBuffer );
	agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
	agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//白背景
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );	

	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, AG_CG_TITLE, 0, &w, &h );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, 0, 0, s(FB_WIDTH), s(FB_HEIGHT));	
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

void runEnd(struct Touch* touch, struct Player* player)
{
	int ID;
	
	for(ID=0; ID<PLAYER_NUM; ID++){
		if(touch[ID].stat==1){
			player[ID].Sync=1;
		}
	}
}

void drawEnd(AGDrawBuffer* DBuf, struct Player* player){
	int w,h,MyID;
	int GAME_RESULT;

	MyID=(int)agPDevSyncGetMyID();
	if(player[MyID].Result==-1)
		GAME_RESULT=AG_CG_YOULOSE;
	else if(player[MyID].Result==0)
		GAME_RESULT=AG_CG_YOUWIN;

	//Init
	agDrawBufferInit( DBuf , DrawBuffer );
	agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
	agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, GAME_RESULT, 0, &w, &h );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, 0, 0, s(FB_WIDTH), s(FB_HEIGHT));		
} 