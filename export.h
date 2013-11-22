#ifndef __AG_EXPORT__
#define __AG_EXPORT__

#include "import.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************/
/*                       FrameBuffer                           */
/***************************************************************/
#define AGE_FB_WIDTH	(1024)
#define AGE_FB_HEIGHT	(768)
#define AGE_DISP_WIDTH	(1024)
#define AGE_DISP_HEIGHT	(768)
#define AGE_FB_ADDR0	(7602176)
#define AGE_FB_ADDR1	(6815744)
#define AGE_ZB_ADDR	(6815744)
#define AGE_ZB_DEPTH	(4)
#define AGE_ZMD	(1)
#define AGE_AAC_ADDR	(13631488)
#define AGE_AAC_SIZE	(13631488)
#define AGE_SOUND_ROM_OFFSET	(0x400000)

/***************************************************************/
/*                    Rom Member Symbol                        */
/***************************************************************/
#define AG_CG_FIELD	(0)
#define AG_CG_NUM_0	(1)
#define AG_CG_NUM_1	(2)
#define AG_CG_NUM_2	(3)
#define AG_CG_NUM_3	(4)
#define AG_CG_NUM_4	(5)
#define AG_CG_NUM_5	(6)
#define AG_CG_NUM_6	(7)
#define AG_CG_NUM_7	(8)
#define AG_CG_NUM_8	(9)
#define AG_CG_NUM_9	(10)
#define AG_CG_SENKAN_DOWN	(11)
#define AG_CG_SENKAN_LEFT	(12)
#define AG_CG_SENKAN_RIGHT	(13)
#define AG_CG_SENKAN_UP	(14)

/***************************************************************/
/*                     RM3 Member Symbol                       */
/***************************************************************/

/***************************************************************/
/*                       Vram Group Symbol                     */
/***************************************************************/

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[15];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
