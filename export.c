#include "export.h"

/***************************************************************/
/*                       Rom Member Lists                      */
/***************************************************************/
const AGERomMember ageRM[] = {
	/*    Offset,  PalOffset,    W,    H,VramW,Type,      Size, Container */
	{          0,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_0 */
	{       2250,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_1 */
	{       4500,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_2 */
	{       6750,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_3 */
	{       9000,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_4 */
	{      11250,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_5 */
	{      13500,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_6 */
	{      15750,          0,   51,   90,   51,  0,      18360, NULL },		/* AG_CG_NUM_7 */
	{      18045,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_8 */
	{      20295,          0,   50,   90,   50,  0,      18000, NULL },		/* AG_CG_NUM_9 */
	{      22545,          0,  500,  500,  500,  0,    1000000, NULL },		/* AG_CG_FIELD */
	{     147545,          0,   50,  250,   50,  0,      50000, NULL },		/* AG_CG_SENKAN_DOWN */
	{     153795,          0,  250,   50,  250,  0,      50000, NULL },		/* AG_CG_SENKAN_LEFT */
	{     160045,          0,  250,   50,  250,  0,      50000, NULL },		/* AG_CG_SENKAN_RIGHT */
	{     166295,          0,   50,  250,   50,  0,      50000, NULL },		/* AG_CG_SENKAN_UP */
	{     172545,          0,  296,  147,  296,  0,     174048, NULL },		/* AG_CG_ATTACK */
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
