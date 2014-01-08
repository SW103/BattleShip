#include "export.h"

/***************************************************************/
/*                       Rom Member Lists                      */
/***************************************************************/
const AGERomMember ageRM[] = {
	/*    Offset,  PalOffset,    W,    H,VramW,Type,      Size, Container */
	{          0,          0,  200,  100,  104,  8,       1632, NULL },		/* AG_CG_KAITEN */
	{        204,          0,   50,   90,   32,  8,        800, NULL },		/* AG_CG_NUM_0_0 */
	{        304,          0,   50,   90,   32,  8,        896, NULL },		/* AG_CG_NUM_1_0 */
	{        416,          0,   50,   90,   32,  8,        960, NULL },		/* AG_CG_NUM_2_0 */
	{        536,          0,   50,   90,   32,  8,        800, NULL },		/* AG_CG_NUM_3_0 */
	{        636,          0,   50,   90,   32,  8,        992, NULL },		/* AG_CG_NUM_4_0 */
	{        760,          0,   50,   90,   32,  8,        832, NULL },		/* AG_CG_NUM_5_0 */
	{        864,          0,   50,   90,   32,  8,        768, NULL },		/* AG_CG_NUM_6_0 */
	{        960,          0,   51,   90,   32,  8,       1088, NULL },		/* AG_CG_NUM_7_0 */
	{       1096,          0,   50,   90,   32,  8,        704, NULL },		/* AG_CG_NUM_8_0 */
	{       1184,          0,   50,   90,   32,  8,        896, NULL },		/* AG_CG_NUM_9_0 */
	{       1296,          0,  500,  500,  256,  8,      11840, NULL },		/* AG_CG_FIELD */
	{       2776,          0,   50,  250,   32,  8,       1344, NULL },		/* AG_CG_SENKAN_DOWN */
	{       2944,          0,  250,   50,  128,  8,       1408, NULL },		/* AG_CG_SENKAN_LEFT */
	{       3120,          0,  250,   50,  128,  8,       1376, NULL },		/* AG_CG_SENKAN_RIGHT */
	{       3292,          0,   50,  250,   32,  8,       1344, NULL },		/* AG_CG_SENKAN_UP */
	{       3460,          0,   50,  250,   32,  8,       1344, NULL },		/* AG_CG_SENKAN_SKELTON_DOWN */
	{       3628,          0,  250,   50,  128,  8,       1376, NULL },		/* AG_CG_SENKAN_SKELTON_LEFT */
	{       3800,          0,  250,   50,  128,  8,       1344, NULL },		/* AG_CG_SENKAN_SKELTON_RIGHT */
	{       3968,          0,   50,  250,   32,  8,       1376, NULL },		/* AG_CG_SENKAN_SKELTON_UP */
	{       4140,          0,  200,  100,  104,  8,       1312, NULL },		/* AG_CG_START */
	{       4304,          0,  500,  100,  256,  8,       4352, NULL },		/* AG_CG_OVERLAP */
	{       4848,          0,  500,  100,  256,  8,       2560, NULL },		/* AG_CG_WAIT */
};

/***************************************************************/
/*                       RM3 Member Lists                      */
/***************************************************************/
const AGERM3Member ageRM3[] = { { 0, 0, 0, 0, 0, 0, 0, NULL } }; /* No RM3 Member */
/***************************************************************/
/*                     Reserve Member Lists                    */
/***************************************************************/
const u32 ageReserve[1] = { 0 }; /* No Reserve Member */

/***************************************************************/
/*                      User Member Lists                      */
/***************************************************************/
const u32 ageUser[1] = { 0 }; /* No User Member */

/***************************************************************/
/*                      Vram Group Lists                       */
/***************************************************************/
const AGEVramGroup ageVG[] = { { 0, NULL } };
const s16 ageVGCnt = 0;

const u8* ageMotCommon[] = { NULL };
const AGEMotion ageMot[] = {
	{ 0, 0, 0, NULL, },
};
/***************************************************************/
/*                   Sound Rom Member Lists                    */
/***************************************************************/
const AGESoundRomMember ageSRM[] = { { 0, 0 } };
/***************************************************************/
/*                      Sound Score Lists                      */
/***************************************************************/
const AGESoundScore ageSS[] = { { 0, 0, 0, -1, NULL } };
