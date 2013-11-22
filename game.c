#include "game.h"

u32 DrawBuffer[ 4096*10 ];

void initGame()
{
	return;
}

void runSet()
{
	return;
}

void runBattle()
{
	return;
}


void drawSet(AGDrawBuffer* DBuf, struct Field* field, struct Player* player)
{
	int i;

	//Init
	agDrawBufferInit( DBuf , DrawBuffer );
	agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
	agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//白背景
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//フィールド
	drawField( DBuf, field);

	//戦艦
	for(i=0;i<5;i++){
		drawBattleShip(DBuf, &(player->battleShip[i]));
	}
	/*
	//数字を描画する場所の白い四角
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 100-20, 100-20, 100+50*10+20, 100+90+20);
	//数字の描画
	drawNumberGraph(20131120, 100,100,50,90,10,DBuf);
	*/
	agDrawEODL( DBuf );
	agTransferDrawDMA( DBuf );

	aglWaitVSync();
	aglSwap();
}

void drawBattle(AGDrawBuffer* DBuf)
{
	return;
}

