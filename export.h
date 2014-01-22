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
#define AG_CG_FIELD 	(11)
#define AG_CG_SENKAN_DOWN	(12)
#define AG_CG_SENKAN_LEFT	(13)
#define AG_CG_SENKAN_RIGHT	(14)
#define AG_CG_SENKAN_UP	(15)
#define AG_CG_SENKAN_SKELTON_DOWN	(16)
#define AG_CG_TURN_BATTLE	(17)
#define AG_CG_REALTIME_BATTLE	(18)
#define AG_CG_YOULOSE	(19)
#define AG_CG_YOUWIN	(20)
#define AG_CG_SENKAN_SKELTON_LEFT	(21)
#define AG_CG_SENKAN_SKELTON_RIGHT	(22)
#define AG_CG_SENKAN_SKELTON_UP	(23)
#define AG_CG_START	(24)
#define AG_CG_OVERLAP	(25)
#define AG_CG_WAIT	(26)
#define AG_CG_ATTACK	(27)
#define AG_CG_TITLE	(28)
#define AG_CG_SCOPE	(29)
#define AG_CG_X	(30)

/***************************************************************/
/*                     RM3 Member Symbol                       */
/***************************************************************/
#define AG_RP_BATTLESHIP_TITLE	(0)
#define AG_RP_OCEAN	(1)
#define AG_RP_NOISE	(2)

/***************************************************************/
/*                       Vram Group Symbol                     */
/***************************************************************/

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[31];
extern const AGERM3Member ageRM3[3];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
