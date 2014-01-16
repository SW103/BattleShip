#ifndef __PLAYER__
#define __PLAYER__

#include "import.h"
#include "battleShip.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Player
{
	struct BattleShip battleShip[5];
	int Sync;
	//0:まだ勝負がついていない。 -1:負け。
	int Result;
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initPlayer(struct Player* player);

int getBattleShip(struct Player* player, int i, int j, struct HoldingObject* hold);
/*
void runSet();
void runBattle();
void drawSet(AGDrawBuffer* DBuf);
void drawBattle(AGDrawBuffer* DBuf);
*/


#ifdef __cplusplus
}
#endif

#endif /* __PLAYER__ */
