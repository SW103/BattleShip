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
#define AG_CG_FIELD__2_	(11)
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
/*                       Sound Member Symbol                   */
/***************************************************************/
#define AS_SND_SAKUSENKAIGI	(0)
#define AS_SND_HISHOU	(1)
#define AS_SND_A01	(2)
#define AS_SND_A02	(3)
#define AS_SND_A03	(4)
#define AS_SND_A04	(5)
#define AS_SND_A05	(6)
#define AS_SND_A06	(7)
#define AS_SND_A07	(8)
#define AS_SND_A08	(9)
#define AS_SND_A09	(10)
#define AS_SND_A10	(11)
#define AS_SND_A11	(12)
#define AS_SND_A12	(13)
#define AS_SND_A13	(14)
#define AS_SND_A14	(15)
#define AS_SND_A15	(16)
#define AS_SND_A16	(17)
#define AS_SND_A17	(18)
#define AS_SND_A18	(19)
#define AS_SND_A19	(20)
#define AS_SND_A20	(21)
#define AS_SND_A21	(22)
#define AS_SND_A22	(23)
#define AS_SND_A23	(24)
#define AS_SND_A24	(25)
#define AS_SND_A25	(26)
#define AS_SND_A26	(27)
#define AS_SND_B01	(28)
#define AS_SND_B02	(29)
#define AS_SND_B03	(30)
#define AS_SND_B04	(31)
#define AS_SND_B05	(32)
#define AS_SND_B06	(33)
#define AS_SND_B07	(34)
#define AS_SND_B08	(35)
#define AS_SND_B09	(36)
#define AS_SND_B10	(37)
#define AS_SND_B11	(38)
#define AS_SND_B12	(39)
#define AS_SND_B13	(40)
#define AS_SND_B14	(41)
#define AS_SND_B15	(42)
#define AS_SND_B16	(43)
#define AS_SND_B17	(44)
#define AS_SND_B18	(45)
#define AS_SND_B19	(46)
#define AS_SND_B20	(47)
#define AS_SND_B21	(48)
#define AS_SND_B22	(49)
#define AS_SND_B23	(50)
#define AS_SND_B24	(51)
#define AS_SND_B25	(52)
#define AS_SND_B26	(53)

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[31];
extern const AGERM3Member ageRM3[3];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const s16 ageVGCnt;
extern const AGESoundRomMember ageSRM[54];

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
