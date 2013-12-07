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
	player->battleShip[1].dir = UP;
	player->battleShip[3].dir = UP;

	player->battleShip[0].bombed[0]=0;
	player->battleShip[0].bombed[1]=1;
	player->battleShip[0].bombed[2]=2;
	player->battleShip[0].bombed[3]=3;
	player->battleShip[0].bombed[4]=4;

	player->battleShip[1].bombed[0]=11;
	player->battleShip[1].bombed[1]=21;
	player->battleShip[1].bombed[2]=31;
	player->battleShip[1].bombed[3]=41;
	player->battleShip[1].bombed[4]=51;

	player->battleShip[2].bombed[0]=22;
	player->battleShip[2].bombed[1]=23;
	player->battleShip[2].bombed[2]=24;
	player->battleShip[2].bombed[3]=25;
	player->battleShip[2].bombed[4]=26;

	player->battleShip[3].bombed[0]=33;
	player->battleShip[3].bombed[1]=43;
	player->battleShip[3].bombed[2]=53;
	player->battleShip[3].bombed[3]=63;
	player->battleShip[3].bombed[4]=73;

	player->battleShip[4].bombed[0]=44;
	player->battleShip[4].bombed[1]=45;
	player->battleShip[4].bombed[2]=46;
	player->battleShip[4].bombed[3]=47;
	player->battleShip[4].bombed[4]=48;
}

int getBattleShip(struct Player* player, int i, int j, struct HoldingObject* hold)
{
	int index;
	//戦艦の初期化
	for(index=0;index<5;index++){
		//_dprintf("index = %d  \n", index);
		//_dprintf("b_i = %d  \n", player->battleShip[index].i);
		//_dprintf("b_j = %d  \n\n", player->battleShip[index].j);
		
		if(isThereBattleShip( &player->battleShip[index], i, j , hold))
			return index;

		/*if( player->battleShip[index].i == i && player->battleShip[index].j == j )
			return index;
		*/
	}
	return -1;
}
