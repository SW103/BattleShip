#ifndef __AGTOUCH_H__
#define __AGTOUCH_H__

#ifdef __cplusplus
extern "C" {
#endif

int agTouchInit(u32 sizex,u32 sizey);
int agTouchGetData(s32 *posx,s32 *posy,s32 *posz, u32 *stat);

#ifdef __cplusplus
}
#endif

#endif // __AGTOUCH_H__