#include <amlib.h>
#include "agtouch.h"

/*7�Z�OLED*/
#define LED_7SEG		(*(volatile unsigned short*) 0xA9000002)


#define FRM_CHCK 4   /* �}�E�X�i�^�b�`�p�l���j���o�܂ł̃��[�v�� */
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
���O :
	int agTouchInit(u32 sizex,u32 sizey)
�@�\ :
	�^�b�`�p�l�����C�u�����̏�����
���� :
	sizex		��ʐ����T�C�Y
	sizey		��ʐ����T�C�Y
�Ԓl :
	1  ����������I��
	0  �������Ɏ��s
	���������A�������ł͖������ɐ���I���B
��� :
   �V���A���^�b�`�p�l�����C�u�����̏��������s���܂��B

   ���� sizex, sizey �� agTouchGetData()�ɂ����W�� �w��͈͓��ɐݒ肷��ׂ�
   �g�p���܂��B

   ���̊֐��́ARS232C(SCI2)�����L�p�����[�^�ŏ��������܂��B
       1200bps  7bit  �p���e�B����  �X�g�b�v�r�b�g1

�ŏI�X�V�� : 2010.11.06
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
    static int sync_loop=0;        // �����f�[�^�Ԋu 
    static int sync_chck=0;        // �����f�[�^�Ԋu�̈�v�� 
    static int _sync_loop=-1;      // �����f�[�^�Ԋu(��r�p�̑O��ޔ�)
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
        if ( (data &  0x80) != 0)	//sync��7bit������
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
            } else	//�G���[
			{
                sync_chck=0;
				data_nums=5; // �G���[���ɂ�5�ɐݒ�(�W��)
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
//    pd |= (data_buff[0] & 0x20)>>5;	//�q�E�_��
//    pd |= (data_buff[0] & 0x10)>>3;	//�q
//    pd |= (data_buff[3] & 0x10)>>2;	//�܂�Ȃ�

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
���O :
    int agTouchGetData(s32 *posx,s32 *posy,s32 *posz,u32 *push)
�@�\ :
    �V���A���^�b�`�p�l���̏����擾
���� :
    posx  �擾�ʒu���i�[��|�C���^
    posy  �擾�ʒu���i�[��|�C���^
    posz  �擾�z�C�[���������i�[��|�C���^
    push  �擾�{�^����Ԕ[��|�C���^
�Ԓl :
    1   ��񂠂�(�ڑ��}�E�X�i�^�b�`�p�l���j���ʍ�)
    0   ���Ȃ�(�ڑ��}�E�X�i�^�b�`�p�l���j���ʃG���[)
��� :
    �V���A���^�b�`�p�l���̏����擾���܂��B

    posx, posy �Ŏ������A�h���X�Ƀ^�b�`�p�l���̍��W���Z�b�g���܂��B

    �Z�b�g�������W�́AagTouchInit()�֐��Ŏw�肵���T�C�Y�ɐ�������܂��B
    posz �Ŏ������A�h���X�Ƀz�C�[���̉�]�̍������Z�b�g���܂��B

    stat �Ŏ������A�h���X�Ƀ}�E�X�{�^���i�^�b�`�p�l���j�̏�Ԃ� OR �ŃZ�b�g���܂��B
        ���{�^�� 0x01
        �E�{�^�� 0x02
        ���{�^�� 0x04  (�z�C�[���̃{�^��)

    ���̊֐��́A����I�ɌĂяo���K�v������܂��B(����SCI2�͊����쓮�ɂȂ��Ă��Ȃ�
    �̂�FIFO�T�C�Y��16Byte���z�����f�[�^����M����ƁA�f�[�^���Ƃ肱�ڂ��܂��B)
    ��1/30�b�Ɉ��ȏ�̌ďo�𐄏��B


�ŏI�X�V�� : 2010.11.06
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
�ȉ�����Ȃ��q
int agTouchInit(u32 sizex,u32 sizey)
{	
	SCIF0.SCSCR.WORD = 0x0000;

	SCIF0.SCFCR.BIT.TFRST = 1;
	SCIF0.SCFCR.BIT.RFRST = 1;

	SCIF0.SCSCR.BIT.CKE = 0;
	
	SCIF0.SCSMR.WORD=0x0000;
	
	SCIF0.SCBRR = 26;

	LED_7SEG = 0x3F00;	//������
	LED_7SEG = 0x3F00;	//������
	LED_7SEG = 0x3F00;	//������
	LED_7SEG = 0x3F00;	//������
	LED_7SEG = 0x3F00;	//������	(WAIT�΍�)
	
	SCIF0.SCFCR.WORD      = 0x0000;
	
	SCIF0.SCSCR.BIT.RE = 1;			//��M�J�n
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
	SCIF0.SCLSR.BIT.ORER= 0;	//�G���[�����̏ȗ�
	
	while(SCIF0.SCFSR.BIT.RDF)	//��M�f�[�^����
	{
		LED_7SEG = 0x7F00;
		rec_buf = SCIF0.SCFRDR;
		*posx = 250;
		*posy = 250;
		SCIF0.SCFSR.BIT.RDF = 0;

		SCIF0.SCFSR.BIT.DR  = 0;
		SCIF0.SCFSR.BIT.ER  = 0;
		SCIF0.SCFSR.BIT.BRK = 0;
		SCIF0.SCLSR.BIT.ORER= 0;	//�G���[�����̏ȗ�
	}
	
	
	return 1;
}

*/
