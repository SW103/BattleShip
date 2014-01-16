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
	MODE_START, MODE_SET, MODE_SET_OVERLAP, MODE_SET_WAIT, MODE_BATTLE, MODE_NUM
};

/***************************************************************/
/*                   Holding Object                            */
/***************************************************************/
struct HoldingObject{
	int isHolding;			//ホールディングしていた1 していなかったら0
	enum FieldObject obj;	//オブジェクトの種類
	int shipIndex;			//戦艦の番号
	int d_i,d_j;			//戦艦の先頭からの相対位置
	struct BattleShip* battleShip;	//戦艦のポインタ	
};


/***************************************************************/
/*                       関数の宣言                              */
/***************************************************************/

void initGame(struct Player* player);
void runStart(struct Touch* touch, struct Player* player);
int runSet(struct Touch* touch, struct Field* field, struct Player* player);
void runBattle(struct Touch* touch, struct Field* field, struct Player* player);
void drawStart(AGDrawBuffer* DBuf);
void drawSet(AGDrawBuffer* DBuf, struct Field* field, struct Player* player, struct Touch* touch);
void drawBattle(AGDrawBuffer* DBuf, struct Field* field, struct Player* player);

// タッチしたオブジェクトの種類を取得
int _getTouchObject(struct Touch* touch/*, struct Field* field*/, struct Player* player, struct HoldingObject* hold);

// リリースした場所を取得
int getReleaseObject(int* i, int* j, struct Touch* touch, struct Field* field, struct Player* player);

// リリースする位置に戦艦を配置できるかどうか
int placeable(struct Touch* touch, struct Field* field, struct HoldingObject* hold);

//回転ボタンが押されたかどうか
int isPushedRotation(struct Touch* touch);
//最後にリリースされた戦艦の回転処理
int rotationBattleShip(struct HoldingObject* hold);

//スタートボタンが押されたかどうか
int isPushedStart(struct Touch* touch);
//重なっている配置があるかどうか
int isOverlap(struct Player* player);


#ifdef __cplusplus
}
#endif

#endif /* __GAME__ */
