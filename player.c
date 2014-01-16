#include "player.h"

void initPlayer(struct Player* player)
{
	int i,ID;
	
	//戦艦の初期化
	for(ID=0;ID<PLAYER_NUM;ID++){
		player[ID].Sync=0;
		for(i=0;i<5;i++){
			player[ID].battleShip[i].i = i;
			player[ID].battleShip[i].j = i;
			player[ID].battleShip[i].len = 5;
			player[ID].battleShip[i].wid = 1;
			player[ID].battleShip[i].life = 5;
			player[ID].battleShip[i].len = 5;
			player[ID].battleShip[i].dir = LEFT;
			player[ID].battleShip[i].visible = 1;
		}
		player[ID].battleShip[1].dir = UP;
		player[ID].battleShip[3].dir = UP;
	}
}

int getBattleShip(struct Player* player, int i, int j)
{
	int index;
	//戦艦の初期化
	for(index=0;index<5;index++){
		if(isThereBattleShip( &player->battleShip[index], i, j ))
			return index;
	}
	return -1;
}
