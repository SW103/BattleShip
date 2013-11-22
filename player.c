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
	}
	player->battleShip[1].dir = RIGHT;
	player->battleShip[2].dir = UP;
	player->battleShip[3].dir = DOWN;
}

