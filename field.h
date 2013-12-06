#ifndef __FIELD__
#define __FIELD__

#include "import.h"

#define ATTACK_BUTTON_X 650
#define ATTACK_BUTTON_Y 500
#define ATTACK_BUTTON_W 300
#define ATTACK_BUTTON_H 100

#ifdef __cplusplus
extern "C" {
#endif

enum FieldStat{
	UNSELECTED, SELECTED, MISS, HIT, FIELD_STATE
};


/***************************************************************/
/*                       Field                                 */
/***************************************************************/
struct Field{
	enum FieldStat field[FIELD_HEIGHT_NUM][FIELD_WIDTH_NUM];
	int selected;
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initField(struct Field* field);
void drawField(AGDrawBuffer* DBuf, struct Field* field, int x, int y, int cell_size);



#ifdef __cplusplus
}
#endif

#endif /* __FIELD__ */
