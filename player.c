#include "player.h"

void initPlayer(struct Player* player)
{
	int i;
	//戦艦の初期化
	for(i=0;i<5;i++){
		player->battleShip[i].i = i;
		player->battleShip[i].j = i;
		player->battleShip[i].len = 5;
		player->battleShip[i].wid = 1;
		player->battleShip[i].life = 1;
		player->battleShip[i].len = 5;
		player->battleShip[i].dir = LEFT;
		player->battleShip[i].visible = 1;
	}
	player->battleShip[1].dir = RIGHT;
	player->battleShip[2].dir = UP;
	player->battleShip[3].dir = DOWN;
}

int getBattleShip(struct Player* player, int i, int j, int *d_i, int *d_j)
{
	int index;
	//戦艦の初期化
	for(index=0;index<5;index++){
		//_dprintf("index = %d  \n", index);
		//_dprintf("b_i = %d  \n", player->battleShip[index].i);
		//_dprintf("b_j = %d  \n\n", player->battleShip[index].j);
		
		if(isThereBattleShip( &player->battleShip[index], i, j , d_i, d_j ))
			return index;

		/*if( player->battleShip[index].i == i && player->battleShip[index].j == j )
			return index;
		*/
	}
	return -1;
}
