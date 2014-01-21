#ifndef __EFFECT__
#define __EFFECT__

#include "import.h"
#include "field.h"
#include "player.h"
#include "touch.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Effect{
	u32 Name;
	u32 Count;
	u32 Frame;
	u32 LastFrame;
	int flag;
};


/***************************************************************/
/*                       関数の宣言                              */
/***************************************************************/

void initEffect(struct Effect* effect);
void countEffect(struct  Effect* effect);

#ifdef __cplusplus
}
#endif

#endif /* __EFFECT__ */
