#include "battleShip.h"

void initBattleShip()
{
	return;
}


void drawBattleShip(AGDrawBuffer* DBuf, struct BattleShip* battleShip)
{
	//戦艦画像の配列
	u16 battleShipGraph[DIR_NUM] = {AG_CG_SENKAN_LEFT,AG_CG_SENKAN_UP,AG_CG_SENKAN_RIGHT,AG_CG_SENKAN_DOWN};
	
	// 不可視ならなにもしない
	if(battleShip->visible == 0)
		return;

	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, battleShipGraph[battleShip->dir], 0, NULL, NULL );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	switch(battleShip->dir){
		case LEFT:
			agDrawSPRITE( DBuf, 1, s(FIELD_X + battleShip->i*CELL_SIZE), s(FIELD_Y + battleShip->j*CELL_SIZE),
				s(FIELD_X + (battleShip->i + battleShip->len)*CELL_SIZE), s(FIELD_Y + (battleShip->j + battleShip->wid)*CELL_SIZE));
			break;
		case UP:
			agDrawSPRITE( DBuf, 1, s(FIELD_X + battleShip->i*CELL_SIZE), s(FIELD_Y + battleShip->j*CELL_SIZE),
				s(FIELD_X + (battleShip->i + battleShip->wid)*CELL_SIZE), s(FIELD_Y + (battleShip->j + battleShip->len)*CELL_SIZE));
			break;
		case RIGHT:
			agDrawSPRITE( DBuf, 1, s(FIELD_X + (battleShip->i - battleShip->len + 1)*CELL_SIZE), s(FIELD_Y + battleShip->j*CELL_SIZE),
				s(FIELD_X + (battleShip->i + 1)*CELL_SIZE), s(FIELD_Y + (battleShip->j + battleShip->wid)*CELL_SIZE));
			break;
		case DOWN:
			agDrawSPRITE( DBuf, 1, s(FIELD_X + battleShip->i*CELL_SIZE), s(FIELD_Y + (battleShip->j - battleShip->len + 1 )*CELL_SIZE),
				s(FIELD_X + (battleShip->i + battleShip->wid)*CELL_SIZE), s(FIELD_Y + (battleShip->j + 1)*CELL_SIZE));
			break;
	}
}

void getBattleShipPosition(struct BattleShip* battleShip, int* i, int* j, int* w, int* l)
{
	switch( battleShip->dir ){
		case LEFT:
			*i = battleShip->i;
			*j = battleShip->j;
			*w = battleShip->len;
			*l = battleShip->wid;
			break;
		case UP:
			*i = battleShip->i - (battleShip->wid - 1);
			*j = battleShip->j;
			*w = battleShip->wid;
			*l = battleShip->len;
			break;
		case RIGHT:
			*i = battleShip->i - (battleShip->len - 1);
			*j = battleShip->j - (battleShip->wid - 1);
			//*j = battleShip->j;
			*w = battleShip->len;
			*l = battleShip->wid;
			break;
		case DOWN:
			*i = battleShip->i;
			*j = battleShip->j - (battleShip->len - 1);
			*w = battleShip->wid;
			*l = battleShip->len;
			break;
		default:
			break;
	}
}

int isThereBattleShip(struct BattleShip* battleShip, int field_i, int field_j)
{
	int i, j, wid, len;

	getBattleShipPosition(battleShip, &i, &j, &wid, &len);

	if( i <= field_i && i + wid > field_i && j <= field_j && j + len > field_j ){
		return 1;
	}
	return 0;
}