#ifndef __BATTLESHIP__
#define __BATTLESHIP__

#include "import.h"

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_BATTLESHIP_HEIGHT_NUM 6
#define MAX_BATTLESHIP_WIDTH_NUM 2

/***************************************************************/
/*                       Direction                             */
/***************************************************************/
enum Direction{
	LEFT,UP,RIGHT,DOWN,DIR_NUM
};


/***************************************************************/
/*                     Object Type                             */
/***************************************************************/
/*
enum ObjectType{
	NULLTYPE, BATTLESHIP, OBJECTTYPE_NUM
};*/




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
	int bombed[MAX_BATTLESHIP_HEIGHT_NUM][MAX_BATTLESHIP_WIDTH_NUM];
};



/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initBattleShip();
void drawBattleShip(AGDrawBuffer* DBuf, struct BattleShip* battleShip);
void drawSkeltonBattleShip(AGDrawBuffer* DBuf, struct BattleShip* battleShip, int touch_x, int touch_y, int d_i, int d_j);

void getBattleShipPosition(struct BattleShip* battleShip, int* i, int* j, int* w, int* l);
int isThereBattleShip(struct BattleShip* battleShip, int field_i, int field_j);



#ifdef __cplusplus
}
#endif

#endif /* __BATTLESHIP__ */
