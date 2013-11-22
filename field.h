#ifndef __FIELD__
#define __FIELD__

#include "export.h"

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



#ifdef __cplusplus
}
#endif

#endif /* __FIELD__ */
