#ifndef __FIELD__
#define __FIELD__

#include "import.h"

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
	int flag;
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initField(struct Field* field);
void drawField(AGDrawBuffer* DBuf, struct Field* field, int x, int y, int cell_size);
void drawFieldColor(AGDrawBuffer* DBuf, struct Field* field, int x, int y, int cell_size);



#ifdef __cplusplus
}
#endif

#endif /* __FIELD__ */
