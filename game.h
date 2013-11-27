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

enum ObjectType{
	NULLTYPE, BATTLESHIP, OBJECTTYPE_NUM
};

struct HoldingObject{
	enum ObjectType type;	//オブジェクトの種類
	int shipIndex;			//戦艦の番号
	int d_i,d_j;			//戦艦の先頭からの相対位置
	
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
int getTouchObject(enum ObjectType* type, struct Touch* touch, struct Field* field, struct Player* player, int* d_i, int* d_j);

// リリースした場所を取得
int getReleaseObject(int* i, int* j, struct Touch* touch, struct Field* field, struct Player* player);

#ifdef __cplusplus
}
#endif

#endif /* __GAME__ */
