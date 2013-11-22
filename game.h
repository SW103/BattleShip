#ifndef __GAME__
#define __GAME__

#include "import.h"
#include "field.h"
#include "player.h"

#ifdef __cplusplus
extern "C" {
#endif

enum GameMode{
	MODE_SET, MODE_BATTLE, MODE_NUM
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initGame();
void runSet();
void runBattle();
void drawSet(AGDrawBuffer* DBuf, struct Field* field, struct Player* player);
void drawBattle(AGDrawBuffer* DBuf);



#ifdef __cplusplus
}
#endif

#endif /* __GAME__ */
