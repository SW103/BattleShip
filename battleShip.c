#include "battleShip.h"

void initBattleShip()
{
	return;
}


void drawBattleShip(AGDrawBuffer* DBuf, struct BattleShip* battleShip, int x, int y, int cell_size)
{
	//戦艦画像の配列
	u16 battleShipGraph[DIR_NUM] = {AG_CG_SENKAN_LEFT,AG_CG_SENKAN_UP,AG_CG_SENKAN_RIGHT,AG_CG_SENKAN_DOWN};
	
	// 不可視ならなにもしない
	if(battleShip->visible == 0){
		//_dprintf("%d",battleShip->i);
		return;
	}

	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, battleShipGraph[battleShip->dir], 0, NULL, NULL );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );

	//_dprintf("%d",battleShip->i);
	switch(battleShip->dir){
		case LEFT:
			agDrawSPRITE( DBuf, 1, x + battleShip->i*cell_size, y + battleShip->j*cell_size,
				x + (battleShip->i + battleShip->len)*cell_size, y + (battleShip->j + battleShip->wid)*cell_size);
			break;
		case UP:
			agDrawSPRITE( DBuf, 1, x + battleShip->i*cell_size, y + battleShip->j*cell_size,
				x + (battleShip->i + battleShip->wid)*cell_size, y + (battleShip->j + battleShip->len)*cell_size);
			break;
		case RIGHT:
			agDrawSPRITE( DBuf, 1, x + (battleShip->i - battleShip->len + 1)*cell_size, y + battleShip->j*cell_size,
				x + (battleShip->i + 1)*cell_size, y + (battleShip->j + battleShip->wid)*cell_size);
			break;
		case DOWN:
			agDrawSPRITE( DBuf, 1, x + battleShip->i*cell_size, y + (battleShip->j - battleShip->len + 1 )*cell_size,
				x + (battleShip->i + battleShip->wid)*cell_size, y + (battleShip->j + 1)*cell_size);
			break;
	}
}

int isThereBattleShip(struct BattleShip* battleShip, int field_i, int field_j, struct HoldingObject* hold)
{
	int i, j, wid, len;

	switch( battleShip->dir ){
		case LEFT:
			i = battleShip->i;
			j = battleShip->j;
			wid = battleShip->len;
			len = battleShip->wid;
			break;
		case UP:
			i = battleShip->i - (battleShip->wid - 1);
			j = battleShip->j;
			wid = battleShip->wid;
			len = battleShip->len;
			break;
		case RIGHT:
			i = battleShip->i - (battleShip->len - 1);
			j = battleShip->j - (battleShip->wid - 1);
			wid = battleShip->len;
			len = battleShip->wid;
			break;
		case DOWN:
			i = battleShip->i;
			j = battleShip->j - (battleShip->len - 1);
			wid = battleShip->wid;
			len = battleShip->len;
			break;
		default:
			break;
	}
	//_dprintf("i = %d  \n", i);
	//_dprintf("j = %d  \n", j);
	//_dprintf("wid = %d  \n", wid);
	//_dprintf("len = %d  \n\n", len);
	if( i <= field_i && i + wid > field_i && j <= field_j && j + len > field_j ){
		hold->d_i = field_i - battleShip->i;
		hold->d_j = field_j - battleShip->j;
		hold->battleShip = battleShip;
		//_dprintf("di = %d  \n", *d_i);
		//_dprintf("dj = %d  \n\n", *d_j);
		return 1;
	}
	return 0;
}
