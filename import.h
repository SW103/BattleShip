#ifndef __IMPORT__
#define __IMPORT__

#ifdef __cplusplus
extern "C" {
#endif

#include "export.h"

// main.cで必要
#include <amlib.h>
#include <agdraw.h>
#include <agesndmgr.h>
#include <agetool.h>
#include <agtransfer.h>
#include <vdpreg.h>
#include <stdlib.h>
#include <agtouch.h>

/***************************************************************/
/*                       define                                */
/***************************************************************/
#define s(x) (x<<2)
//#define KEY_NUM 8
#define FIELD_WIDTH_NUM 10
#define FIELD_HEIGHT_NUM 10
#define CELL_SIZE 50
#define FIELD_X 150
#define FIELD_Y 100

/***************************************************************/
/*                    Field Object                             */
/***************************************************************/
enum FieldObject{
	NULLOBJECT, BATTLESHIP, OBJECT_NUM
};


#ifdef __cplusplus
}
#endif

#endif /* __IMPORT__ */
