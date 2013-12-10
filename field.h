#ifndef __FIELD__
#define __FIELD__

#include "import.h"


#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************/
/*                    Field Object                             */
/***************************************************************/
enum FieldObject{
	NONE_OBJ, BATTLESHIP_OBJ, ATTACKEDSHIP_OBJ, ATTACKEDPOINT_OBJ
};


/***************************************************************/
/*                       Field                                 */
/***************************************************************/
struct Field{
	/*
	int field[FIELD_HEIGHT_NUM][FIELD_WIDTH_NUM];			//フィールド情報
	int virtualField[FIELD_HEIGHT_NUM][FIELD_WIDTH_NUM];	//仮想フィールド情報
	*/
	int field[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM];			//フィールド情報
	int virtualField[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM];	//仮想フィールド情報
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initField(struct Field* field);
void drawField(AGDrawBuffer* DBuf, struct Field* field);


void addShipToField(struct BattleShip* battleShip);

void removeShipFromField();




#ifdef __cplusplus
}
#endif

#endif /* __FIELD__ */
