#ifndef __GAME__
#define __GAME__

#include "import.h"
#include "field.h"
#include "player.h"
#include "touch.h"

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
void runSet(struct Touch* touch, struct Field* field, struct Player* player);
void runBattle();
void drawSet(AGDrawBuffer* DBuf, struct Field* field, struct Player* player);
void drawBattle(AGDrawBuffer* DBuf);

// タッチしたオブジェクトの種類を取得
int getTouchObject(enum ObjectType* type, struct Touch* touch, struct Field* field, struct Player* player, struct HoldingObject* hold);

// リリースした場所を取得
int getReleaseObject(int* i, int* j, struct Touch* touch, struct Field* field, struct Player* player);

// リリースする位置に戦艦を配置できるかどうか
int placeable(int i, int j, struct Player* player, struct HoldingObject* hold);
	//フィールド上の適正な位置に配置できるかどうか
	int placeableField();
	//他の戦艦と衝突していないかどうか
	int placeableBattleShip();

#ifdef __cplusplus
}
#endif

#endif /* __GAME__ */
