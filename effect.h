#ifndef __EFFECT__
#define __EFFECT__

#include "import.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Effect
{
	struct BattleShip battleShip[5];
	int Sync;
	//0:まだ勝負がついていない。 -1:負け。
	int Result;
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initEffect(struct Effect* effect);

void drawEffect(AGDrawBuffer* DBuf, struct Effect* effect)

#ifdef __cplusplus
}
#endif

#endif /* __EFFECT__ */
