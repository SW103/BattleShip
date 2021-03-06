#include "field.h"

void initField(struct Field* field)
{
	int i,j;
	for(i=0;i<FIELD_HEIGHT_NUM;i++){
		for(j=0;j<FIELD_WIDTH_NUM;j++){
			field->field[i][j] = 0;
			field->vietualField[i][j] = 0;
		}
	}
}


void drawField(AGDrawBuffer* DBuf, struct Field* field)
{
	//背景画像
	u16 fieldGraph = AG_CG_FIELD;

	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, fieldGraph, 0, NULL, NULL );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, s(FIELD_X), s(FIELD_Y), s(FIELD_X+CELL_SIZE*FIELD_WIDTH_NUM), s(FIELD_Y+CELL_SIZE*FIELD_HEIGHT_NUM));
}

