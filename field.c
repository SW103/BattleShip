#include "field.h"

void initField(struct Field* field)
{	
	int i,j;
	for(i=0; i<=FIELD_HEIGHT_NUM; i++){
		for(j=0; j<=FIELD_WIDTH_NUM;j++){
			field->field[i][j]=UNSELECTED;
		}
	}
	field->selected = -1;
}

void drawField(AGDrawBuffer* DBuf, struct Field* field, int x, int y, int cell_size)
{
	int i,j;

	//背景画像
	u16 fieldGraph = AG_CG_FIELD;

	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, fieldGraph, 0, NULL, NULL );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, x, y, x+cell_size*FIELD_WIDTH_NUM, y+cell_size*FIELD_HEIGHT_NUM);

	for(i=0; i<FIELD_HEIGHT_NUM; i++){
		for(j=0; j<FIELD_WIDTH_NUM;j++){
			if(field->field[i][j]==SELECTED){
				agDrawSETFCOLOR( DBuf, ARGB( 128, 255, 0, 128 ) );
				agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
				agDrawSPRITE( DBuf, 0, x+cell_size*j, y+cell_size*i, x+cell_size*(j+1), y+cell_size*(i+1) );
			}else if(field->field[i][j]==ATTACKED){
				agDrawSETFCOLOR( DBuf, ARGB( 128, 0, 0, 0 ) );
				agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
				agDrawSPRITE( DBuf, 0, x+cell_size*j, y+cell_size*i, x+cell_size*(j+1), y+cell_size*(i+1) );
			}
		}
	}
}
