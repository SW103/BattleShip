#include "effect.h"


void initEffect(struct Effect* effect)
{
        effect->Count=0;
        effect->Frame=0;
        effect->flag = 1;
        return;
}

void countEffect(struct Effect* effect){
        effect->Count += 1;
        if(effect->Count > 5){
                effect->Count = 0;
                if(effect->flag==1){
                        effect->Frame += 1;
                        if(effect->Frame >= effect->LastFrame){
                                effect->flag = -1;
                        }
                }else{
                        effect->Frame -= 1;
                        if(effect->Frame <= 0){
                                effect->flag = 1;
                        }                        
                }
        }
}
