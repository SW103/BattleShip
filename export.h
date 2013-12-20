#ifndef __AG_EXPORT__
#define __AG_EXPORT__

#include <agexport.h>
#include <ag3d.h>

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
#define AG_CG_KAITEN	(0)
#define AG_CG_NUM_0_0	(1)
#define AG_CG_NUM_1_0	(2)
#define AG_CG_NUM_2_0	(3)
#define AG_CG_NUM_3_0	(4)
#define AG_CG_NUM_4_0	(5)
#define AG_CG_NUM_5_0	(6)
#define AG_CG_NUM_6_0	(7)
#define AG_CG_NUM_7_0	(8)
#define AG_CG_NUM_8_0	(9)
#define AG_CG_NUM_9_0	(10)
#define AG_CG_FIELD	(11)
#define AG_CG_SENKAN_DOWN	(12)
#define AG_CG_SENKAN_LEFT	(13)
#define AG_CG_SENKAN_RIGHT	(14)
#define AG_CG_SENKAN_UP	(15)
#define AG_CG_SENKAN_SKELTON_DOWN	(16)
#define AG_CG_SENKAN_SKELTON_LEFT	(17)
#define AG_CG_SENKAN_SKELTON_RIGHT	(18)
#define AG_CG_SENKAN_SKELTON_UP	(19)

/***************************************************************/
/*                     RM3 Member Symbol                       */
/***************************************************************/

/***************************************************************/
/*                       Vram Group Symbol                     */
/***************************************************************/

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[20];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
