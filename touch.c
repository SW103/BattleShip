#include "touch.h"


void initTouch(struct Touch* touch)
{
	int i;
	for(i=0;i<PLAYER_NUM;i++){
		touch[i].x = 0;
		touch[i].y = 0;
		touch[i].count = 0;
	}
}

void getTouch(struct Touch* touch)
{
	int i, stat, posz;
	for( i=0 ; i < PLAYER_NUM ; i++ ) {
		agPDevSyncGetData(i,&(touch[i].x),&(touch[i].y),&(touch[i].stat));

		//タッチが放されたとき
		if(touch[i].count > 0 && touch[i].stat == 0){
			touch[i].count = -1;
		}else if(touch[i].count == -1){
			touch[i].count = 0;
		}else{
			if(stat>0)
				touch[i].count++;
		}
	}
}