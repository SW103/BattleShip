#include "touch.h"


void initTouch(struct Touch* touch)
{
	touch->x = 0;
	touch->y = 0;
	touch->count = 0;
}

void getTouch(struct Touch* touch)
{
	int stat, posz;
	agTouchGetData( &touch->x, &touch->y, &posz, &stat );

	//タッチが放されたとき
	if(touch->count > 0 && stat == 0){
		touch->count = -1;
	}else{
		touch->count = stat;
	}
}