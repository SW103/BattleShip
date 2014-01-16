#ifndef __TOUCH__
#define __TOUCH__

#include "import.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Touch{
	//タッチ座標
	int x, y;

	u32 stat;
	// タッチされてないとき 	0
	// タッチされた瞬間 		1
	// タッチが放された瞬間 	-1
	int count;
};

/***************************************************************/
/*                       関数の宣言                             */
/***************************************************************/

void initTouch(struct Touch* touch);
void getTouch(struct Touch* touch);



#ifdef __cplusplus
}
#endif

#endif /* __TOUCH__ */
