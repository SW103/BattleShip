#ifndef __FIELD__
#define __FIELD__

#include "import.h"


#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************/
/*                       Field                                 */
/***************************************************************/
struct Field{
	int filed[FIELD_HEIGHT_NUM][FIELD_WIDTH_NUM];
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initField();
void drawField(AGDrawBuffer* DBuf, struct Field* field);


void addShipToField(struct BattleShip* battleShip);

void removeShipFromField();

//フィールド情報の更新
void updateField(struct Field* field, struct Player* player);



#ifdef __cplusplus
}
#endif

#endif /* __FIELD__ */
