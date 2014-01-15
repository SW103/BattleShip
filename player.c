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

		player[ID].battleShip[0].bombed[0]=0;
		player[ID].battleShip[0].bombed[1]=1;
		player[ID].battleShip[0].bombed[2]=2;
		player[ID].battleShip[0].bombed[3]=3;
		player[ID].battleShip[0].bombed[4]=4;

		player[ID].battleShip[1].bombed[0]=11;
		player[ID].battleShip[1].bombed[1]=21;
		player[ID].battleShip[1].bombed[2]=31;
		player[ID].battleShip[1].bombed[3]=41;
		player[ID].battleShip[1].bombed[4]=51;

		player[ID].battleShip[2].bombed[0]=22;
		player[ID].battleShip[2].bombed[1]=23;
		player[ID].battleShip[2].bombed[2]=24;
		player[ID].battleShip[2].bombed[3]=25;
		player[ID].battleShip[2].bombed[4]=26;

		player[ID].battleShip[3].bombed[0]=33;
		player[ID].battleShip[3].bombed[1]=43;
		player[ID].battleShip[3].bombed[2]=53;
		player[ID].battleShip[3].bombed[3]=63;
		player[ID].battleShip[3].bombed[4]=73;

		player[ID].battleShip[4].bombed[0]=44;
		player[ID].battleShip[4].bombed[1]=45;
		player[ID].battleShip[4].bombed[2]=46;
		player[ID].battleShip[4].bombed[3]=47;
		player[ID].battleShip[4].bombed[4]=48;
	}
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
