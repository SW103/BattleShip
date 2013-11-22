#include "battleShip.h"

void initBattleShip()
{
	return;
}


void drawBattleShip(AGDrawBuffer* DBuf, struct BattleShip* battleShip)
{
	//戦艦画像の配列
	u16 battleShipGraph[DIR_NUM] = {AG_CG_SENKAN_LEFT,AG_CG_SENKAN_UP,AG_CG_SENKAN_RIGHT,AG_CG_SENKAN_DOWN};
	
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

