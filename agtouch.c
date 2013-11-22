#include <amlib.h>
#include "agtouch.h"

/*7セグLED*/
#define LED_7SEG		(*(volatile unsigned short*) 0xA9000002)


#define FRM_CHCK 4   /* マウス（タッチパネル）検出までのループ回数 */
#ifdef DEBUG
#define TOUCH_DEBUG
#endif

static u32 L_SCALE_X = 0;
static u32 L_SCALE_Y = 0;

static int agTouchInit_Flag = 0;
static int touch_data_exist=0;

extern s32 IoSci2_Init(int bps,int b7,int pe,int oe,int s2);
extern void IoSci2_SetRTS( u32 data );
extern s32 IoSci2_RecvData(u8 *data);

/****************************************************************************
名前 :
	int agTouchInit(u32 sizex,u32 sizey)
機能 :
	タッチパネルライブラリの初期化
引数 :
	sizex		画面水平サイズ
	sizey		画面垂直サイズ
返値 :
	1  初期化正常終了
	0  初期化に失敗
	※ただし、現実装では無条件に正常終了。
解説 :
   シリアルタッチパネルライブラリの初期化を行います。

   引数 sizex, sizey は agTouchGetData()による座標を 指定範囲内に設定する為に
   使用します。

   この関数は、RS232C(SCI2)を下記パラメータで初期化します。
       1200bps  7bit  パリティ無し  ストップビット1

最終更新日 : 2010.11.06
****************************************************************************/
int agTouchInit(u32 sizex,u32 sizey)
{
    L_SCALE_X = sizex;
    L_SCALE_Y = sizey;

#ifdef TOUCH_DEBUG
_dprintf("agTouchInit(%d,%d,*tick_count,%d)\n",sizex,sizey);
#endif

    IoSci2_Init(9600,0,0,0,0);
    IoSci2_SetRTS(0);
    agTouchInit_Flag = 1;
    return(1);
}

static int _agTouchData( s32 *posx , s32 *posy , s32 *posz , u32 *push )
{
    static int sync_loop=0;        // 同期データ間隔 
    static int sync_chck=0;        // 同期データ間隔の一致回数 
    static int _sync_loop=-1;      // 同期データ間隔(比較用の前回退避)
    static int data_nums=5;

    static int  init_flag=0;
    static u8 data_buff[5];
    static u32 data_rpos=0;
    static s32 px=0;
    static s32 py=0;
    static u32 pd=0;
	s16 abs;

    if ( !init_flag )
	{
        px = L_SCALE_X/2;
        py = L_SCALE_Y/2;
        init_flag=1;
    }
    while(1)
	{
        u8 data;
        if ( !IoSci2_RecvData(&data) )
		{
            *posx=px;
            *posy=py;
            *posz=0;
            *push=pd;
            return(0);
        }
        sync_loop++;
        if ( (data &  0x80) != 0)	//syncの7bitを示す
		{
            if ( sync_loop < 8 && _sync_loop == sync_loop )
			{
                if ( sync_chck < FRM_CHCK )
				{
                    sync_chck++;
                } else if ( sync_chck == FRM_CHCK )
				{
                    sync_chck=FRM_CHCK+1;
                    data_nums=sync_loop;
                    touch_data_exist=1;
//					LED_7SEG = 0x3F00;
                }
            } else	//エラー
			{
                sync_chck=0;
				data_nums=5; // エラー時には5に設定(標準)
                touch_data_exist=0;
//				LED_7SEG = 0xFF00;
            }
            _sync_loop=sync_loop;
            sync_loop=0;
            data_buff[0]=data;
            data_rpos=1;
        } else
		{
            if ( data_rpos < 5 )
			{
                data_buff[data_rpos]=data;
            }
            data_rpos++;
        }

        if ( data_rpos == data_nums && sync_chck > FRM_CHCK )
		{
            while( data_rpos < 5 )
			{
                data_buff[data_rpos]=0;
                data_rpos++;
            }
            break;
        }
    }
    data_rpos=0;

    pd &= ~0x07;
	pd |= (data_buff[0] & 0x40)>>6;
//    pd |= (data_buff[0] & 0x20)>>5;	//ヒ・ダリ
//    pd |= (data_buff[0] & 0x10)>>3;	//Ｒ
//    pd |= (data_buff[3] & 0x10)>>2;	//まんなか

	abs = ((data_buff[2] & 0x7f)<<4) | ((data_buff[1] & 0x78)>>3);
	px = L_SCALE_X-abs*L_SCALE_X/2048;
	abs = ((data_buff[4] & 0x7f)<<4) | ((data_buff[3] & 0x78)>>3);
	py = abs*L_SCALE_Y/2048;

    *posx = px;
    *posy = py;
    *posz = 0;
    *push = pd;

    return(1);
}

/****************************************************************************
名前 :
    int agTouchGetData(s32 *posx,s32 *posy,s32 *posz,u32 *push)
機能 :
    シリアルタッチパネルの情報を取得
引数 :
    posx  取得位置情報格納先ポインタ
    posy  取得位置情報格納先ポインタ
    posz  取得ホイール差分情報格納先ポインタ
    push  取得ボタン状態納先ポインタ
返値 :
    1   情報あり(接続マウス（タッチパネル）判別済)
    0   情報なし(接続マウス（タッチパネル）判別エラー)
解説 :
    シリアルタッチパネルの情報を取得します。

    posx, posy で示されるアドレスにタッチパネルの座標をセットします。

    セットされる座標は、agTouchInit()関数で指定したサイズに制限されます。
    posz で示されるアドレスにホイールの回転の差分をセットします。

    stat で示されるアドレスにマウスボタン（タッチパネル）の状態を OR でセットします。
        左ボタン 0x01
        右ボタン 0x02
        中ボタン 0x04  (ホイールのボタン)

    この関数は、定期的に呼び出す必要があります。(現在SCI2は割込駆動になっていない
    のでFIFOサイズの16Byteこ越えたデータを受信すると、データをとりこぼします。)
    ※1/30秒に一回以上の呼出を推奨。


最終更新日 : 2010.11.06
****************************************************************************/
int agTouchGetData( s32 *posx , s32 *posy , s32 *posz , u32 *stat ) 
{
    s32 px,py;
    u32 pd;
    s32 pz;
    int  res;
    static int   init_skip=64;

    if ( !agTouchInit_Flag )
	{
        return(0);
    }
    while( init_skip > 0 )
	{
        u8 data;
        init_skip--;
        if ( !IoSci2_RecvData(&data) )
		{
            return(0);
        }
    }

    *stat = 0;
    *posz = 0;
    while(1)
	{
        res=_agTouchData(&px,&py,&pz,&pd);
        *posz += pz;
        *stat |= pd;
        if ( !res )
		{
            break;
        }
    }
    *posx = px;
    *posy = py;

    return(touch_data_exist);
}

/*---------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
以下いらない子
int agTouchInit(u32 sizex,u32 sizey)
{	
	SCIF0.SCSCR.WORD = 0x0000;

	SCIF0.SCFCR.BIT.TFRST = 1;
	SCIF0.SCFCR.BIT.RFRST = 1;

	SCIF0.SCSCR.BIT.CKE = 0;
	
	SCIF0.SCSMR.WORD=0x0000;
	
	SCIF0.SCBRR = 26;

	LED_7SEG = 0x3F00;	//初期化
	LED_7SEG = 0x3F00;	//初期化
	LED_7SEG = 0x3F00;	//初期化
	LED_7SEG = 0x3F00;	//初期化
	LED_7SEG = 0x3F00;	//初期化	(WAIT対策)
	
	SCIF0.SCFCR.WORD      = 0x0000;
	
	SCIF0.SCSCR.BIT.RE = 1;			//受信開始
	SCIF0.SCSCR.BIT.TE = 1;
	
	return 1;
}

int agTouchGetData(s32 *posx,s32 *posy,s32 *posz,u32 *stat)
{
	unsigned char rec_buf;
//	LED_7SEG = 0x0600;
//	LED_7SEG = (SCIF0.SCSCR.WORD<<8);
//	LED_7SEG = (SCIF0.SCBRR<<8);
//	LED_7SEG = (SCIF0.SCSMR.WORD<<8);
	LED_7SEG = (SCIF0.SCSCR.WORD<<8);
	*posx = 500;
	*posy = 500;	
	
	SCIF0.SCFSR.BIT.DR  = 0;
	SCIF0.SCFSR.BIT.ER  = 0;
	SCIF0.SCFSR.BIT.BRK = 0;
	SCIF0.SCLSR.BIT.ORER= 0;	//エラー処理の省略
	
	while(SCIF0.SCFSR.BIT.RDF)	//受信データあり
	{
		LED_7SEG = 0x7F00;
		rec_buf = SCIF0.SCFRDR;
		*posx = 250;
		*posy = 250;
		SCIF0.SCFSR.BIT.RDF = 0;

		SCIF0.SCFSR.BIT.DR  = 0;
		SCIF0.SCFSR.BIT.ER  = 0;
		SCIF0.SCFSR.BIT.BRK = 0;
		SCIF0.SCLSR.BIT.ORER= 0;	//エラー処理の省略
	}
	
	
	return 1;
}

*/
