#ifndef __BATTLESHIP__
#define __BATTLESHIP__

#include "import.h"

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_BATTLESHIP_HEIGHT_NUM 6
#define MAX_BATTLESHIP_WIDTH_NUM 2
#define MAX_BATTLESHIP_LENGTH 5

/***************************************************************/
/*                       Direction                             */
/***************************************************************/
enum Direction{
	LEFT,UP,RIGHT,DOWN,DIR_NUM
};


/***************************************************************/
/*                     Object Type                             */
/***************************************************************/
enum ObjectType{
	NULLTYPE, BATTLESHIP, OBJECTTYPE_NUM
};


/***************************************************************/
/*                       BattleShip                            */
/***************************************************************/
struct BattleShip{
	int i,j;			//始点
	int len,wid;		//長さ、幅
	enum Direction dir;	//向いている方向
	int life;			//ライフ
	int visible;		//可視状態  0:不可視  1:可視
	//被弾箇所の配列
	int bombed[MAX_BATTLESHIP_LENGTH];
};

/***************************************************************/
/*                   Holding Object                            */
/***************************************************************/
struct HoldingObject{
	enum ObjectType type;	//オブジェクトの種類
	int shipIndex;			//戦艦の番号
	int d_i,d_j;			//戦艦の先頭からの相対位置
	struct BattleShip* battleShip;	//戦艦のポインタ	
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initBattleShip();
void drawBattleShip(AGDrawBuffer* DBuf, struct BattleShip* battleShip, int x, int y, int cell_size);

int isThereBattleShip(struct BattleShip* battleShip, int field_i, int field_j, struct HoldingObject* hold);



#ifdef __cplusplus
}
#endif

#endif /* __BATTLESHIP__ */
