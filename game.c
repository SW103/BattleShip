#include "game.h"

u32 DrawBuffer[ 4096*10 ];

struct HoldingObject hold[2];

void initGame(struct Player* player)
{
	hold[0].battleShip = player[0].battleShip;
	hold[1].battleShip = player[1].battleShip;
	return;
}

void runStart(struct Touch* touch, struct Player* player)
{
        int ID;
        
        for(ID=0; ID<PLAYER_NUM; ID++){
            if(touch[ID].stat==1){
                    player[ID].Sync=1;
            }
        }
}

void drawStart(AGDrawBuffer* DBuf,struct Effect* effect)
{
    int w,h;

    //Init
    agDrawBufferInit( DBuf , DrawBuffer );
    agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
    agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

    //白背景
    agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
    agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
    agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );
    
    ageTransferAAC_RM3( DBuf , AG_RP_BATTLESHIP_TITLE , 0 , &w , &h , effect->Frame );
    agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
    agDrawSPRITE( DBuf, 1, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );
    
}

void runSelect(struct Touch* touch, struct Player* player, int* battlemode)
{
        int ID;
        
        for(ID=0; ID<PLAYER_NUM; ID++){
            if(isPushedButton(&touch[ID],512-200,200,512+200,200+100)==1){
                if(touch[ID].stat==1){
                    player[ID].Sync=1;
                }
                *battlemode = MODE_BATTLE;
            }else if(isPushedButton(&touch[ID],512-200,400,512+200,400+100)==1){
                if(touch[ID].stat==1){
                    player[ID].Sync=1;
                }
                *battlemode = MODE_TURNBATTLE;
            }
        }


}

void drawSelect(AGDrawBuffer* DBuf, struct Player* player)
{
    int w,h;

    //Init
    agDrawBufferInit( DBuf , DrawBuffer );
    agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
    agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

    //白背景
    agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
    agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
    agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

    //リアルタイム制
    agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
    ageTransferAAC( DBuf, AG_CG_REALTIME_BATTLE, 0, NULL, NULL );
    agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
    agDrawSPRITE( DBuf, 1, s(512 - 200), s(200), s(512 + 200), s(200+100));    

    //ターン制
    agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
    ageTransferAAC( DBuf, AG_CG_TURN_BATTLE, 0, NULL, NULL );
    agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
    agDrawSPRITE( DBuf, 1, s(512 - 200), s(400), s(512 + 200), s(400+100));


}


int runSet(struct Touch* touch, struct Field* field, struct Player* player)
{
	int index = -1;
	int i, j;
	int ID/*,_ID*/;

	//_dprintf("runSet1 Sync=%d\n",);
	for(ID=0;ID<PLAYER_NUM;ID++){
		//_dprintf("runSet1 id=%d Sync=%d\n",ID,player[ID].Sync);
		/*
        if(ID==0){
                _ID=1;
        }else{
                _ID=0;
        } 
        */
        //戦艦が重なっているとき
        if(player[ID].Sync==1){
      		_dprintf("runSet1!\n");
        	if(touch[ID].count==1){
        		_dprintf("runSet2!\n");
				player[ID].Sync = 0;
			}
        }else{

        	//セット処理
			if(touch[ID].count == 1){
				//_dprintf("	runSet4!\n");
				index = getTouchObject(&touch[ID]/*, field*/, &player[ID], &hold[ID]);
				//_dprintf("runSet! index = %d\n",index);
				//_dprintf("index = %d \n", index);
				if( index >= 0/* && type == BATTLESHIP*/ ){
				//_dprintf("	runSet6!\n");
					//タッチされた戦艦を不可視にする
					player[ID].battleShip[index].visible = 0;
					//戦艦をつかむ
					hold[ID].shipIndex = index;
					//ホールディングフラグを立てる
					hold[ID].isHolding = 1;
					/*
					_dprintf("h_dir:%d\n",player->battleShip[hold.shipIndex].dir);
					_dprintf("h_i:%d\n",player->battleShip[hold.shipIndex].i);
					_dprintf("h_j:%d\n",player->battleShip[hold.shipIndex].j);
					_dprintf("h_wid:%d\n",player->battleShip[hold.shipIndex].wid);
					_dprintf("h_len:%d\n\n",player->battleShip[hold.shipIndex].len);
					*/
				}else{
					//ホールディングフラグを下げる
					hold[ID].isHolding = 0;	
				}
			}else if(touch[ID].count == -1 && hold[ID].obj != NONE_OBJ){
				//_dprintf("release!\n");
				index = getReleaseObject(&i, &j, &touch[ID], &field[ID], &player[ID]);
				//_dprintf("i = %d  \n", i);
				//_dprintf("j = %d  \n\n", j);
				//_dprintf("index:%d\n",index);
				if( index == 1 && placeable(&touch[ID], &field[ID], &hold[ID]) == 1 ){ // 盤上でリリースしたとき
					//_dprintf("move!\n");
					//放された戦艦の位置を変更する
					//player->battleShip[hold.shipIndex].i = i - hold.d_i;
					//player->battleShip[hold.shipIndex].j = j - hold.d_j;
					/*
					_dprintf("r_dir:%d\n",player->battleShip[hold.shipIndex].dir);
					_dprintf("r_i:%d\n",player->battleShip[hold.shipIndex].i);
					_dprintf("r_j:%d\n",player->battleShip[hold.shipIndex].j);
					_dprintf("r_wid:%d\n",player->battleShip[hold.shipIndex].wid);
					_dprintf("r_len:%d\n\n",player->battleShip[hold.shipIndex].len);
					*/
					player[ID].battleShip[hold[ID].shipIndex].i = i + hold[ID].d_i;
					player[ID].battleShip[hold[ID].shipIndex].j = j + hold[ID].d_j;
				}
				//放された戦艦を可視にする
				player[ID].battleShip[hold[ID].shipIndex].visible = 1;
				//なにもつかんでいない
				hold[ID].shipIndex = -1;
				//ホールディングフラグを下げる
				hold[ID].isHolding = 0;
			}

			//回転ボタン
			if(isPushedButton(&touch[ID],300, 600, 300 + 200, 600+100)==1){
				//_dprintf("Pushed!\n");
				rotationBattleShip(&hold[ID]);
			}
			//スタートボタン
			if(isPushedButton(&touch[ID],600,600,600+200,600+100)==1){
				//_dprintf("START Pushed!\n");
				//重なっているとき
				if(isOverlap(&player[ID])==1){
					_dprintf("runSet3!\n");
					player[ID].Sync = 1;
				}else{
					_dprintf("runSet4!\n");
					player[ID].Sync = 2;
				}
			}
		}
	}
	return 0;
}

void drawSet(AGDrawBuffer* DBuf, struct Field* field, struct Player* player, struct Touch* touch, struct Effect* effect)
{
	int i, MyID, w, h;

	MyID=(int)agPDevSyncGetMyID();

	//Init
	agDrawBufferInit( DBuf , DrawBuffer );
	agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
	agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//白背景
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

    ageTransferAAC_RM3( DBuf , AG_RP_OCEAN , 0 , &w , &h , effect->Frame );
    agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
    agDrawSPRITE( DBuf, 1, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

	//フィールド
	drawField( DBuf, field, s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));

	//戦艦
	for(i=0;i<5;i++){
		drawBattleShip(DBuf, &(player[MyID].battleShip[i]));
	}

	if(hold[MyID].isHolding == 1){
		//_dprintf("Skelton!\n");
		{
			int x = touch[MyID].x;
			int y = touch[MyID].y;
			//_dprintf("x:%d\n",x);
			//_dprintf("y:%d\n\n",y);
			// 範囲内のとき
			if( (x >= FIELD_X) && (y >= FIELD_Y) && (x <= FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) && (y <= FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
				//_dprintf("Skelton2!\n\n");
				x = (x - FIELD_X)/CELL_SIZE;
				y = (y - FIELD_Y)/CELL_SIZE;
				//ホールディング戦艦
				drawSkeltonBattleShip(DBuf, hold[MyID].battleShip, x, y, hold[MyID].d_i, hold[MyID].d_j);
			}
		}
	}
	
	//回転ボタン
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, AG_CG_KAITEN, 0, NULL, NULL );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, s(300), s(600), s(300 + 200), s(600+100));

	//スタートボタン
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
	ageTransferAAC( DBuf, AG_CG_START, 0, NULL, NULL );
	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( DBuf, 1, s(600), s(600), s(600 + 200), s(600+100));

	if(player[MyID].Sync==1){
		//戦艦が重なっています
		agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
		ageTransferAAC( DBuf, AG_CG_OVERLAP, 0, NULL, NULL );
		agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
		agDrawSPRITE( DBuf, 1, s(250), s(300), s(250 + 500), s(300+100));
	}

	if(player[MyID].Sync==2){
		//待機しています
		agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
		ageTransferAAC( DBuf, AG_CG_WAIT, 0, NULL, NULL );
		agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
		agDrawSPRITE( DBuf, 1, s(250), s(300), s(250 + 500), s(300+100));
	}

	/*
	//数字を描画する場所の白い四角
	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
	agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( DBuf, 0, 100-20, 100-20, 100+50*10+20, 100+90+20);
	//数字の描画
	drawNumberGraph(20131120, 100,100,50,90,10,DBuf);
	*/
	
}

void runBattle(struct Touch* touch, struct Field* field, struct Player* player)
{
        int i,x,y;
        int w,h;
        int index,ID,EnID,MyID;

        //デバッグ用
        MyID=(int)agPDevSyncGetMyID();
        if(MyID==0){
                MyID=1;
        }else{
                MyID=0;
        }

        for(ID=0;ID<PLAYER_NUM;ID++){
                if(ID==0){
                        EnID=1;
                }else{
                        EnID=0;
                }                

                //攻撃ボタンが押され、かつマスが選択されていたら攻撃を行う。
                if( (touch[ID].x >= ATTACK_BUTTON_X) 
                        && (touch[ID].x < ATTACK_BUTTON_X+ATTACK_BUTTON_W) 
                        && (touch[ID].y >= ATTACK_BUTTON_Y) 
                        && (touch[ID].y < ATTACK_BUTTON_Y+ATTACK_BUTTON_H) ){
                        if(field[EnID].selected_x!=-1 && field[EnID].selected_y!=-1){

                                //index = getBattleShip(&player[EnID], field[EnID].selected%10, field[EnID].selected/10, &hold );
                        		index = getBattleShip(&player[EnID], field[EnID].selected_x, field[EnID].selected_y);
                                if(index != -1){
                                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=HIT;
                                        player[EnID].battleShip[index].life += -1;
                                }else{
                                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=MISS;                        
                                }
                        }
                        field[EnID].selected_x=-1;
                        field[EnID].selected_y=-1;
                }

                //フィールドが押された時の。
                if( (touch[ID].x >= FIELD_X) 
                        && (touch[ID].y >= FIELD_Y) 
                        && (touch[ID].x < FIELD_X+CELL_SIZE*FIELD_WIDTH_NUM)
                        && (touch[ID].y < FIELD_Y+CELL_SIZE*FIELD_HEIGHT_NUM) ){

                        x = (touch[ID].x - FIELD_X)/CELL_SIZE;
                        y = (touch[ID].y - FIELD_Y)/CELL_SIZE;

                        if( field[EnID].field[y][x]==UNSELECTED ){
                
                                for(h=0; h<FIELD_HEIGHT_NUM; h++){
                                        for(w=0; w<FIELD_WIDTH_NUM; w++){
                                                if(field[EnID].field[h][w]==SELECTED){
                                                        field[EnID].field[h][w]=UNSELECTED;        
                                                }
                                        }
                                }

                        field[EnID].selected_x=x;
                        field[EnID].selected_y=y;

                        field[EnID].field[y][x]=SELECTED;
                        }else if( field[EnID].field[y][x]==HIT || field[EnID].field[y][x]==MISS ){
                                if(field[EnID].selected_x != -1 && field[EnID].selected_y != -1){
                                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=UNSELECTED;
                                        field[EnID].selected_x = -1;
                                        field[EnID].selected_y = -1;
                                }
                        }
                }else{
                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=UNSELECTED;
                        field[EnID].selected_x = -1;
                        field[EnID].selected_y = -1;        
                }
        }
}

void runTurnBattle(struct Touch* touch, struct Field* field, struct Player* player, int *turnID)
{
        int i,x,y;
        int w,h;
        int index,EnID,ID;

        ID = *turnID;

                if(ID==0){
                        EnID=1;
                }else{
                        EnID=0;
                }                

                //攻撃ボタンが押され、かつマスが選択されていたら攻撃を行う。
                if( (touch[ID].x >= ATTACK_BUTTON_X) 
                        && (touch[ID].x < ATTACK_BUTTON_X+ATTACK_BUTTON_W) 
                        && (touch[ID].y >= ATTACK_BUTTON_Y) 
                        && (touch[ID].y < ATTACK_BUTTON_Y+ATTACK_BUTTON_H) ){
                        if(field[EnID].selected_x!=-1 && field[EnID].selected_y!=-1){
                        		*turnID=EnID;
                        		index = getBattleShip(&player[EnID], field[EnID].selected_x, field[EnID].selected_y);
                                if(index != -1){
                                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=HIT;
                                        player[EnID].battleShip[index].life += -1;
                                }else{
                                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=MISS;                        
                                }
                        }
                        field[EnID].selected_x=-1;
                        field[EnID].selected_y=-1;
                }

                //フィールドが押された時の。
                if( (touch[ID].x >= FIELD_X) 
                        && (touch[ID].y >= FIELD_Y) 
                        && (touch[ID].x < FIELD_X+CELL_SIZE*FIELD_WIDTH_NUM)
                        && (touch[ID].y < FIELD_Y+CELL_SIZE*FIELD_HEIGHT_NUM) ){

                        x = (touch[ID].x - FIELD_X)/CELL_SIZE;
                        y = (touch[ID].y - FIELD_Y)/CELL_SIZE;

                        if( field[EnID].field[y][x]==UNSELECTED ){
                
                                for(h=0; h<FIELD_HEIGHT_NUM; h++){
                                        for(w=0; w<FIELD_WIDTH_NUM; w++){
                                                if(field[EnID].field[h][w]==SELECTED){
                                                        field[EnID].field[h][w]=UNSELECTED;        
                                                }
                                        }
                                }

                        field[EnID].selected_x=x;
                        field[EnID].selected_y=y;

                        field[EnID].field[y][x]=SELECTED;
                        }else if( field[EnID].field[y][x]==HIT || field[EnID].field[y][x]==MISS ){
                                if(field[EnID].selected_x != -1 && field[EnID].selected_y != -1){
                                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=UNSELECTED;
                                        field[EnID].selected_x = -1;
                                        field[EnID].selected_y = -1;
                                }
                        }
                }else{
                        field[EnID].field[field[EnID].selected_y][field[EnID].selected_x]=UNSELECTED;
                        field[EnID].selected_x = -1;
                        field[EnID].selected_y = -1;        
                }
}

void drawBattle(AGDrawBuffer* DBuf, struct Field* field, struct Player* player, struct Effect* effect)
{
        int i,w,h,MyID,EnID;
        int x,y;

        MyID=(int)agPDevSyncGetMyID();
        if(MyID==0){
                EnID=1;
        }else{
                EnID=0;
        }

        //Init
        agDrawBufferInit( DBuf , DrawBuffer );
        agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
        agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

        //白背景
        agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 255, 255 ) );
        agDrawSETDBMODE( DBuf, 0xff, 0, 0, 1 );
        agDrawSPRITE( DBuf, 0, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

        //敵のフィールド
        ageTransferAAC_RM3( DBuf , AG_RP_OCEAN , 0 , &w , &h , effect->Frame );
        agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
        agDrawSPRITE( DBuf, 1, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );

        drawField( DBuf, field, s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));
        drawFieldColor( DBuf, &field[EnID], s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));

        for(i=0;i<5;i++){
                if(player[EnID].battleShip[i].life == 0)
                        drawBattleShip2( DBuf, &(player[EnID].battleShip[i]), s(FIELD_X), s(FIELD_Y), s(CELL_SIZE));
        }

        //自分のフィールド
        drawField( DBuf, field, s(700), s(125), s(30));
        drawFieldColor( DBuf, &field[MyID], s(700), s(125), s(30));

        for(i=0;i<5;i++){
                drawBattleShip2( DBuf, &(player[MyID].battleShip[i]), s(700), s(125), s(30));
        }

        //攻撃ボタン
        agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
        ageTransferAAC( DBuf, AG_CG_ATTACK, 0, &w, &h );
        agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
        agDrawSPRITE( DBuf, 1, s(ATTACK_BUTTON_X), s(ATTACK_BUTTON_Y), s(ATTACK_BUTTON_X)+s(ATTACK_BUTTON_W), s(ATTACK_BUTTON_Y)+s(ATTACK_BUTTON_H) );        
}

void runEnd(struct Touch* touch, struct Player* player)
{
        int ID;
        
        for(ID=0; ID<PLAYER_NUM; ID++){
                if(touch[ID].stat==1){
                        player[ID].Sync=1;
                }
        }
}

void drawEnd(AGDrawBuffer* DBuf, struct Player* player){
        int w,h,MyID;

        MyID=(int)agPDevSyncGetMyID();
        //Init
        agDrawBufferInit( DBuf , DrawBuffer );
        agDrawSETDAVR( DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
        agDrawSETDAVF( DBuf, 0, 0, s(FB_WIDTH), s(FB_HEIGHT) );
        if(player[MyID].Result==-1){
        	agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
       		ageTransferAAC( DBuf, AG_CG_YOULOSE, 0, &w, &h );
        	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
        	agDrawSPRITE( DBuf, 1, 0, 0, s(FB_WIDTH), s(FB_HEIGHT)); 
        }else{
            agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
        	ageTransferAAC( DBuf, AG_CG_YOUWIN, 0, &w, &h );
        	agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
        	agDrawSPRITE( DBuf, 1, 0, 0, s(FB_WIDTH), s(FB_HEIGHT));                
        }         
}


// タッチしたオブジェクトの種類を取得
int getTouchObject(struct Touch* touch/*, struct Field* field*/, struct Player* player, struct HoldingObject* hold)
{
	int x = touch->x;
	int y = touch->y;
	int t_i, t_j;	//タッチしたi,j
	int ship_index;
	int i, j, wid, len;

	//_dprintf("	getTouchObject! x = %d\n",x);
	//_dprintf("	getTouchObject! y = %d\n",y);

	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		hold->obj = NONE_OBJ;
		return -1;
	}

	// 範囲内のとき
	t_i = (x - FIELD_X)/CELL_SIZE;
	t_j = (y - FIELD_Y)/CELL_SIZE;

	// もし戦艦がいるのなら戦艦の番号を取得
	// もし戦艦がいないのなら -1 
	ship_index = getBattleShip(player, t_i, t_j);

	//_dprintf("	getTouchObject! ship_index = %d\n",ship_index);

	//戦艦がいないとき
	if(ship_index == -1){
		hold->obj = NONE_OBJ;
		return -1;
	}

	//バトルシップの位置を取得
	getBattleShipPosition(hold->battleShip, &i, &j, &wid, &len);

	//hold->d_i = i - player->battleShip[ship_index].i;
	//hold->d_j = j - player->battleShip[ship_index].j;
	hold->d_i = player->battleShip[ship_index].i - t_i;
	hold->d_j = player->battleShip[ship_index].j - t_j;
	//_dprintf("d_i = %d  \n", hold->d_i);
	//_dprintf("d_j = %d  \n\n", hold->d_j);
	hold->battleShip = player->battleShip + ship_index;
	hold->obj = BATTLESHIP_OBJ;
	
	return ship_index;
}

// リリースした場所を取得
int getReleaseObject(int* i, int* j, struct Touch* touch, struct Field* field, struct Player* player)
{
	int x = touch->x;
	int y = touch->y;

	// 範囲外のとき
	if( (x < FIELD_X) || (y < FIELD_Y) || (x > FIELD_X + CELL_SIZE*FIELD_WIDTH_NUM) || (y > FIELD_Y + CELL_SIZE*FIELD_HEIGHT_NUM) ){
		//*type = NULLTYPE;
		return -1;
	}

	// 範囲内のとき
	*i = (x - FIELD_X)/CELL_SIZE;
	*j = (y - FIELD_Y)/CELL_SIZE;
	
	return 1;
}


// リリースする位置に戦艦を配置できるかどうか
int placeable(struct Touch* touch, struct Field* field, struct HoldingObject* hold)
{
	int touch_i = touch->x;
	int touch_j = touch->y;
	int i, j, wid, len;
	int w,h;
	int d_i,d_j;	//保持座標（戦艦の左上座標からの相対値）
	struct BattleShip virShip;	//仮想戦艦
	/*
	//バトルシップの位置を取得
	getBattleShipPosition(hold->battleShip, &i, &j, &wid, &len);
	_dprintf("dir:%d\n",hold->battleShip->dir);
		_dprintf("i:%d\n",i);
		_dprintf("j:%d\n",j);
		_dprintf("wid:%d\n",wid);
		_dprintf("len:%d\n\n",len);
	*/
	// タッチされた場所
	touch_i = (touch_i - FIELD_X)/CELL_SIZE;
	touch_j = (touch_j - FIELD_Y)/CELL_SIZE;

	virShip.i = hold->d_i + touch_i;
	virShip.j = hold->d_j + touch_j;
	virShip.wid = hold->battleShip->wid;
	virShip.len = hold->battleShip->len;
	virShip.dir = hold->battleShip->dir;
	//_dprintf("vi:%d\n",virShip.i);
	//_dprintf("vj:%d\n",virShip.j);
	//_dprintf("vwid:%d\n",virShip.wid);
	//_dprintf("vlen:%d\n\n",virShip.len);

	//仮想戦艦の位置を取得
	getBattleShipPosition(&virShip, &i, &j, &wid, &len);

	//_dprintf("i:%d\n",i);
	//_dprintf("j:%d\n",j);
	//_dprintf("wid:%d\n",wid);
	//_dprintf("len:%d\n\n",len);

	if(i < 0 || i+wid > FIELD_WIDTH_NUM || j < 0 || j+len > FIELD_HEIGHT_NUM)
		return -1;

	/*
	//放した位置がフィールド内かどうかを調べる
	switch(hold->battleShip->dir){
		case LEFT:
			d_i = hold->d_i;
			d_j = hold->d_j;
			break;
		case UP:
			d_i = hold->d_i;
			d_j = hold->d_j;
			break;
		case RIGHT:
			d_i = hold->d_i + hold->battleShip->wid - 1;
			d_j = hold->d_j;
			break;
		case DOWN:
			d_i = hold->d_i;
			d_j = hold->d_j + hold->battleShip->len - 1;
			break;
		default:
			break;
	}

	if(touch_i-d_i < 0 || touch_i-d_i+wid > FIELD_WIDTH_NUM
		|| touch_j-d_j < 0 || touch_j-d_j+len > FIELD_HEIGHT_NUM)
		return -1;
	*/

	return 1;
}

//回転ボタンが押されたかどうか
int isPushedButton(struct Touch* touch, int b_x1, int b_y1, int b_x2, int b_y2)
{
	int x = touch->x;
	int y = touch->y;

	if( x>=b_x1 && x<b_x2 && y>=b_y1 && y<b_y2 && touch->count == 1)
		return 1;
	return 0;
}

//最後にリリースされた戦艦の回転処理
int rotationBattleShip(struct HoldingObject* hold)
{
	int i, j, wid, len;
	int k;
	for(k=0;k<DIR_NUM;k++){
		//最後にホールドしていた戦艦の方向を反時計回転
		hold->battleShip->dir = (hold->battleShip->dir + 1)%DIR_NUM;
		//バトルシップの位置を取得
		getBattleShipPosition(hold->battleShip, &i, &j, &wid, &len);
		/*
		_dprintf("dir:%d\n",hold->battleShip->dir);
		_dprintf("i:%d\n",i);
		_dprintf("j:%d\n",j);
		_dprintf("wid:%d\n",wid);
		_dprintf("len:%d\n\n",len);
*/
		//盤面からはみだしていなければブレイク
		if(i>=0 && j>=0 && i+wid<=FIELD_WIDTH_NUM && j+len<=FIELD_HEIGHT_NUM)
			break;
	}
}

//重なっている配置があるかどうか
int isOverlap(struct Player* player)
{
	struct Field field;
	int i, j, wid, len;
	int k,w,l;

	//initField(&field);
	//フィールドの初期化
	for(i=0;i<FIELD_HEIGHT_NUM;i++){
		for(j=0;j<FIELD_WIDTH_NUM;j++){
			field.field[i][j] = 0;
		}
	}

	for(k=0;k<5;k++){
		//バトルシップの位置を取得
		getBattleShipPosition(&player->battleShip[k], &i, &j, &wid, &len);
		//フィールドにバトルシップ情報を格納
		for(w=i;w<i+wid;w++){
			for(l=j;l<j+len;l++){
				//すでに戦艦がいた場合、重なっているので、1を返す
				if(field.field[l][w] == 1){
					return 1;
				}
				field.field[l][w] = 1;
			}
		}
	}

	return 0;
}