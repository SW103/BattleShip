#include "game.h"

u32 DrawBuffer[ 4096*10 ];

struct HoldingObject hold;

void initGame(struct Player* player)
{
	hold.battleShip = player->battleShip;
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
			_dprintf("h_dir:%d\n",player->battleShip[hold.shipIndex].dir);
			_dprintf("h_i:%d\n",player->battleShip[hold.shipIndex].i);
			_dprintf("h_j:%d\n",player->battleShip[hold.shipIndex].j);
			_dprintf("h_wid:%d\n",player->battleShip[hold.shipIndex].wid);
			_dprintf("h_len:%d\n\n",player->battleShip[hold.shipIndex].len);
		}

	}else if(touch->count == -1 && hold.obj != NONE_OBJ){
		_dprintf("release!\n");
		index = getReleaseObject(&i, &j, touch, field, player);
		//_dprintf("i = %d  \n", i);
		//_dprintf("j = %d  \n\n", j);
		_dprintf("index:%d\n",index);
		if( index == 1 && placeable(touch, field, &hold) == 1 ){ // 盤上でリリースしたとき
			_dprintf("move!\n");
			//放された戦艦の位置を変更する
			//player->battleShip[hold.shipIndex].i = i - hold.d_i;
			//player->battleShip[hold.shipIndex].j = j - hold.d_j;
			_dprintf("r_dir:%d\n",player->battleShip[hold.shipIndex].dir);
			_dprintf("r_i:%d\n",player->battleShip[hold.shipIndex].i);
			_dprintf("r_j:%d\n",player->battleShip[hold.shipIndex].j);
			_dprintf("r_wid:%d\n",player->battleShip[hold.shipIndex].wid);
			_dprintf("r_len:%d\n\n",player->battleShip[hold.shipIndex].len);
			player->battleShip[hold.shipIndex].i = i + hold.d_i;
			player->battleShip[hold.shipIndex].j = j + hold.d_j;
		}
		//放された戦艦を可視にする
		player->battleShip[hold.shipIndex].visible = 1;
		//なにもつかんでいない
		hold.shipIndex = -1;
	}

	//回転ボタン
	if(isPushedRotation(touch)==1){
		_dprintf("Pushed!\n");
		rotationBattleShip(&hold);
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
int getTouchObject(struct Touch* touch/*, struct Field* field*/, struct Player* player, struct HoldingObject* hold)
{
	int x = touch->x;
	int y = touch->y;
	int t_i, t_j;	//タッチしたi,j
	int ship_index;
	int i, j, wid, len;


	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		hold->obj = NONE_OBJ;
		return -1;
	}

	// 範囲内のとき
	t_i = (x - FIELD_X)/CELL_SIZE;
	t_j = (y - FIELD_Y)/CELL_SIZE;

	// もし戦艦がいるのなら戦艦の番号を取得
	// もし戦艦がいないのなら -1 
	ship_index = getBattleShip(player, t_i, t_j);

	//戦艦がいないとき
	if(ship_index == -1){
		hold->obj = NONE_OBJ;
		return -1;
	}

	//バトルシップの位置を取得
	getBattleShipPosition(hold->battleShip, &i, &j, &wid, &len);

	//hold->d_i = i - player->battleShip[ship_index].i;
	//hold->d_j = j - player->battleShip[ship_index].j;
	hold->d_i = player->battleShip[ship_index].i - t_i;
	hold->d_j = player->battleShip[ship_index].j - t_j;
	_dprintf("d_i = %d  \n", hold->d_i);
	_dprintf("d_j = %d  \n\n", hold->d_j);
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
	int w,h;
	int d_i,d_j;	//保持座標（戦艦の左上座標からの相対値）
	struct BattleShip virShip;	//仮想戦艦
	/*
	//バトルシップの位置を取得
	getBattleShipPosition(hold->battleShip, &i, &j, &wid, &len);
	_dprintf("dir:%d\n",hold->battleShip->dir);
		_dprintf("i:%d\n",i);
		_dprintf("j:%d\n",j);
		_dprintf("wid:%d\n",wid);
		_dprintf("len:%d\n\n",len);
	*/
	// タッチされた場所
	touch_i = (touch_i - FIELD_X)/CELL_SIZE;
	touch_j = (touch_j - FIELD_Y)/CELL_SIZE;

	virShip.i = hold->d_i + touch_i;
	virShip.j = hold->d_j + touch_j;
	virShip.wid = hold->battleShip->wid;
	virShip.len = hold->battleShip->len;
	virShip.dir = hold->battleShip->dir;
	_dprintf("vi:%d\n",virShip.i);
	_dprintf("vj:%d\n",virShip.j);
	_dprintf("vwid:%d\n",virShip.wid);
	_dprintf("vlen:%d\n\n",virShip.len);

	//仮想戦艦の位置を取得
	getBattleShipPosition(&virShip, &i, &j, &wid, &len);

	_dprintf("i:%d\n",i);
	_dprintf("j:%d\n",j);
	_dprintf("wid:%d\n",wid);
	_dprintf("len:%d\n\n",len);

	if(i < 0 || i+wid > FIELD_WIDTH_NUM || j < 0 || j+len > FIELD_HEIGHT_NUM)
		return -1;

	/*
	//放した位置がフィールド内かどうかを調べる
	switch(hold->battleShip->dir){
		case LEFT:
			d_i = hold->d_i;
			d_j = hold->d_j;
			break;
		case UP:
			d_i = hold->d_i;
			d_j = hold->d_j;
			break;
		case RIGHT:
			d_i = hold->d_i + hold->battleShip->wid - 1;
			d_j = hold->d_j;
			break;
		case DOWN:
			d_i = hold->d_i;
			d_j = hold->d_j + hold->battleShip->len - 1;
			break;
		default:
			break;
	}

	if(touch_i-d_i < 0 || touch_i-d_i+wid > FIELD_WIDTH_NUM
		|| touch_j-d_j < 0 || touch_j-d_j+len > FIELD_HEIGHT_NUM)
		return -1;
	*/

	return 1;
}

//回転ボタンが押されたかどうか
int isPushedRotation(struct Touch* touch)
{
	int x = touch->x;
	int y = touch->y;
	int b_x1 = 300;
	int b_y1 = 600;
	int b_x2 = 300+200;
	int b_y2 = 600+100;

	if( x>=b_x1 && x<b_x2 && y>=b_y1 && y<b_y2 && touch->count == 1)
		return 1;
	return 0;
}

//最後にリリースされた戦艦の回転処理
int rotationBattleShip(struct HoldingObject* hold)
{
	int i, j, wid, len;
	int k;
	for(k=0;k<DIR_NUM;k++){
		//最後にホールドしていた戦艦の方向を反時計回転
		hold->battleShip->dir = (hold->battleShip->dir + 1)%DIR_NUM;
		//バトルシップの位置を取得
		getBattleShipPosition(hold->battleShip, &i, &j, &wid, &len);
		/*
		_dprintf("dir:%d\n",hold->battleShip->dir);
		_dprintf("i:%d\n",i);
		_dprintf("j:%d\n",j);
		_dprintf("wid:%d\n",wid);
		_dprintf("len:%d\n\n",len);
*/
		//盤面からはみだしていなければブレイク
		if(i>=0 && j>=0 && i+wid<=FIELD_WIDTH_NUM && j+len<=FIELD_HEIGHT_NUM)
			break;
	}
}
