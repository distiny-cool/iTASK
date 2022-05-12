#include "..\User\bsp\ov7725\bsp_ov7725.h"
#include "..\User\bsp\ov7725\bsp_sccb.h"
#include "../lcd/bsp_ili9341_lcd.h"
//#include "bsp_ili9341_lcd.h"

//����ͷ��ʼ������
//ע�⣺ʹ�����ַ�ʽ��ʼ���ṹ�壬Ҫ��c/c++ѡ����ѡ�� C99 mode
OV7725_MODE_PARAM cam_mode =
{
	
/*���°�����������ͷ���ã������в��ԣ�����һ�飬����������ע�͵�����*/
/************����1*********������ʾ*****************************/
	
	.QVGA_VGA = 0,	//QVGAģʽ
	.cam_sx = 0,
	.cam_sy = 0,	
	
	.cam_width = 320,
	.cam_height = 240,
	
	.lcd_sx = 0,
	.lcd_sy = 0,
	.lcd_scan = 3, //LCDɨ��ģʽ�����������ÿ���1��3��5��7ģʽ
	
	//���¿ɸ����Լ�����Ҫ������������Χ���ṹ�����Ͷ���	
	.light_mode = 0,//�Զ�����ģʽ
	.saturation = 0,	
	.brightness = 0,
	.contrast = 0,
	.effect = 0,		//����ģʽ
	
	
/**********����2*********������ʾ****************************/	
/*������ʾ��ҪVGAģʽ��ͬ�ֱ�������£���QVGA֡���Ե�*/
/*VGAģʽ�ֱ���Ϊ640*480������ȡ��240*320��ͼ�����������ʾ*/
/*�����̲�֧�ֳ���320*240�� 240*320�ķֱ�������*/

//	.QVGA_VGA = 1,	//VGAģʽ
//	//ȡVGAģʽ���еĴ��ڣ��ɸ���ʵ����Ҫ����
//	.cam_sx = (640-240)/2,
//	.cam_sy = (480-320)/2,	
//	
//	.cam_width = 240, 
//	.cam_height = 320, //��VGAģʽ�£���ֵ�ſ��Դ���240
//	
//	.lcd_sx = 0,
//	.lcd_sy = 0,
//	.lcd_scan = 0, //LCDɨ��ģʽ�����������ÿ���0��2��4��6ģʽ
//	
//	//���¿ɸ����Լ�����Ҫ������������Χ���ṹ�����Ͷ���
//	.light_mode = 0,//�Զ�����ģʽ
//	.saturation = 0,	
//	.brightness = 0,
//	.contrast = 0,
//	.effect = 0,		//����ģʽ
	
	
	/*******����3************С�ֱ���****************************/	
	/*С��320*240�ֱ��ʵģ���ʹ��QVGAģʽ,���õ�ʱ��ע��Һ�����߽�*/
	
//	.QVGA_VGA = 0,	//QVGAģʽ
//	//ȡQVGAģʽ���еĴ��ڣ��ɸ���ʵ����Ҫ����
//	.cam_sx = (320-100)/2,
//	.cam_sy = (240-150)/2,	
//	
//	.cam_width = 100, 
//	.cam_height = 150, 
//	
//	/*Һ��������ʾλ��Ҳ���Ը�����Ҫ������ע�ⲻҪ�����߽缴��*/
//	.lcd_sx = 50,
//	.lcd_sy = 50,
//	.lcd_scan = 3, //LCDɨ��ģʽ��0-7ģʽ��֧�֣�ע�ⲻҪ�����߽缴��

//	//���¿ɸ����Լ�����Ҫ������������Χ���ṹ�����Ͷ���	
//	.light_mode = 0,//�Զ�����ģʽ
//	.saturation = 0,	
//	.brightness = 0,
//	.contrast = 0,
//	.effect = 0,		//����ģʽ

};



typedef struct Reg
{
	uint8_t Address;			       /*�Ĵ�����ַ*/
	uint8_t Value;		           /*�Ĵ���ֵ*/
}Reg_Info;

/* �Ĵ����������� */
Reg_Info Sensor_Config[] =
{
	{CLKRC,     0x00}, /*clock config*/
	{COM7,      0x46}, /*QVGA RGB565 */
	{HSTART,    0x3f},//0x17
	{HSIZE,     0x50},//0x18//{HSIZE,     0x50},//0x18
	{VSTART,    0x03},//0x19
	{VSIZE,     0x78},//0x1A
	{HREF,      0x00},//0x32
	{HOutSize,  0x50},//0x29
	{VOutSize,  0x78},//0x2C
	{EXHCH,     0x00},//0x2A

	/*DSP control*/
	{TGT_B,     0x7f},
	{FixGain,   0x09},
	{AWB_Ctrl0, 0xe0},
	{DSP_Ctrl1, 0xff},
	{DSP_Ctrl2, 0x20},
	{DSP_Ctrl3,	0x00},
	{DSP_Ctrl4, 0x00},

	/*AGC AEC AWB*/
	{COM8,		  0xf0},
	{COM4,		  0x81}, /*Pll AEC CONFIG*/
	{COM6,		  0xc5},
	{COM9,		  0x21},
	{BDBase,	  0xFF},
	{BDMStep,	  0x01},
	{AEW,		    0x34},
	{AEB,		    0x3c},
	{VPT,		    0xa1},
	{EXHCL,		  0x00},
	{AWBCtrl3,  0xaa},
	{COM8,		  0xff},
	{AWBCtrl1,  0x5d},

	{EDGE1,		  0x0a},
	{DNSOff,	  0x01},
	{EDGE2,		  0x01},
	{EDGE3,		  0x01},

	{MTX1,		  0x5f},
	{MTX2,		  0x53},
	{MTX3,		  0x11},
	{MTX4,		  0x1a},
	{MTX5,		  0x3d},
	{MTX6,		  0x5a},
	{MTX_Ctrl,  0x1e},

	{BRIGHT,	  0x00},
	{CNST,		  0x25},
	{USAT,		  0x65},
	{VSAT,		  0x65},
	{UVADJ0,	  0x81},
	{SDE,		    0x06},
	
    /*GAMMA config*/
	{GAM1,		  0x0c},
	{GAM2,		  0x16},
	{GAM3,		  0x2a},
	{GAM4,		  0x4e},
	{GAM5,		  0x61},
	{GAM6,		  0x6f},
	{GAM7,		  0x7b},
	{GAM8,		  0x86},
	{GAM9,		  0x8e},
	{GAM10,		  0x97},
	{GAM11,		  0xa4},
	{GAM12,		  0xaf},
	{GAM13,		  0xc5},
	{GAM14,		  0xd7},
	{GAM15,		  0xe8},
	{SLOP,		  0x20},

	{HUECOS,	  0x80},
	{HUESIN,	  0x80},
	{DSPAuto,	  0xff},
	{DM_LNL,	  0x00},
	{BDBase,	  0x99},
	{BDMStep,	  0x03},
	{LC_RADI,	  0x00},
	{LC_COEF,	  0x13},
	{LC_XC,		  0x08},
	{LC_COEFB,  0x14},
	{LC_COEFR,  0x17},
	{LC_CTR,	  0x05},
	
	{COM3,		  0xd0},/*Horizontal mirror image*/

	/*night mode auto frame rate control*/
	{COM5,		0xf5},	 /*��ҹ�ӻ����£��Զ�����֡�ʣ���֤���նȻ�������*/
	//{COM5,		0x31},	/*ҹ�ӻ���֡�ʲ���*/
};

u8 OV7725_REG_NUM = sizeof(Sensor_Config)/sizeof(Sensor_Config[0]);	  /*�ṹ�������Ա��Ŀ*/

uint8_t Ov7725_vsync = 0;	 /* ֡ͬ���źű�־�����жϺ�����main��������ʹ�� */


/************************************************
 * ��������FIFO_GPIO_Config
 * ����  ��FIFO GPIO����
 * ����  ����
 * ���  ����
 * ע��  ����
 ************************************************/
static void FIFO_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
		/*PD3(FIFO_WEN--FIFOдʹ��)*/
	  macOV7725_WE_SCK_APBxClock_FUN ( macOV7725_WE_GPIO_CLK, ENABLE );
		GPIO_InitStructure.GPIO_Pin = macOV7725_WE_GPIO_PIN;
		GPIO_Init(macOV7725_WE_GPIO_PORT, &GPIO_InitStructure);
	
		/*PB5(FIFO_WRST--FIFOд��λ)*/
		macOV7725_WRST_SCK_APBxClock_FUN ( macOV7725_WRST_GPIO_CLK, ENABLE );
		GPIO_InitStructure.GPIO_Pin = macOV7725_WRST_GPIO_PIN;
		GPIO_Init(macOV7725_WRST_GPIO_PORT, &GPIO_InitStructure);
	
		/*PA2(FIFO_RRST--FIFO����λ) PA3(FIFO_OE--FIFO���ʹ��)*/
    macOV7725_RRST_SCK_APBxClock_FUN ( macOV7725_RRST_GPIO_CLK, ENABLE );
		GPIO_InitStructure.GPIO_Pin = macOV7725_RRST_GPIO_PIN;
		GPIO_Init(macOV7725_RRST_GPIO_PORT, &GPIO_InitStructure);
		
		macOV7725_CS_SCK_APBxClock_FUN ( macOV7725_CS_GPIO_CLK, ENABLE );
		GPIO_InitStructure.GPIO_Pin = macOV7725_CS_GPIO_PIN;
		GPIO_Init(macOV7725_CS_GPIO_PORT, &GPIO_InitStructure);
		
		/*PC5(FIFO_RCLK-FIFO��ʱ��)*/
		macOV7725_RCLK_SCK_APBxClock_FUN ( macOV7725_RCLK_GPIO_CLK, ENABLE );
		GPIO_InitStructure.GPIO_Pin = macOV7725_RCLK_GPIO_PIN;
		GPIO_Init(macOV7725_RCLK_GPIO_PORT, &GPIO_InitStructure);

    /*PB8-PB15(FIFO_DATA--FIFO�������)*/
		macOV7725_DATA_SCK_APBxClock_FUN ( macOV7725_DATA_GPIO_CLK, ENABLE );
		GPIO_InitStructure.GPIO_Pin = macOV7725_DATA_0_GPIO_PIN | macOV7725_DATA_1_GPIO_PIN | macOV7725_DATA_2_GPIO_PIN | macOV7725_DATA_3_GPIO_PIN |
		                              macOV7725_DATA_4_GPIO_PIN | macOV7725_DATA_5_GPIO_PIN | macOV7725_DATA_6_GPIO_PIN | macOV7725_DATA_7_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(macOV7725_DATA_GPIO_PORT, &GPIO_InitStructure);
		
		
    FIFO_CS_L();	  					/*����ʹFIFO���ʹ��*/
    FIFO_WE_H();   						/*����ʹFIFOд����*/
}

void Ov7725_GPIO_Config(void)
{
	SCCB_GPIO_Config();
	FIFO_GPIO_Config();
}

/************************************************
 * ��������VSYNC_GPIO_Configuration
 * ����  ��OV7725 GPIO����
 * ����  ����
 * ���  ����
 * ע��  ����
 ************************************************/
static void VSYNC_GPIO_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;	
	
	  macOV7725_VSYNC_SCK_APBxClock_FUN ( macOV7725_VSYNC_GPIO_CLK, ENABLE );	  /*PA0---VSYNC*/
    GPIO_InitStructure.GPIO_Pin =  macOV7725_VSYNC_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(macOV7725_VSYNC_GPIO_PORT, &GPIO_InitStructure);
}

/************************************************
 * ��������VSYNC_NVIC_Configuration
 * ����  ��VSYNC�ж�����
 * ����  ����
 * ���  ����
 * ע��  ����
 ************************************************/
static void VSYNC_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = macOV7725_VSYNC_EXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/************************************************
 * ��������VSYNC_EXTI_Configuration
 * ����  ��OV7725 VSYNC�жϹܽ�����
 * ����  ����
 * ���  ����
 * ע��  ����
 ************************************************/
/*               ___                            ___
 * VSYNC:     __|   |__________________________|   |__     
 */
static void VSYNC_EXTI_Configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
	
		GPIO_EXTILineConfig(macOV7725_VSYNC_EXTI_SOURCE_PORT, macOV7725_VSYNC_EXTI_SOURCE_PIN);
    EXTI_InitStructure.EXTI_Line = macOV7725_VSYNC_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising ; /*�����ش���*/
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_GenerateSWInterrupt(macOV7725_VSYNC_EXTI_LINE);	/*�жϹҵ� EXTI_Line0  ��*/
}

/************************************************
 * ��������VSYNC_Init
 * ����  ��OV7725 VSYNC�ж��������
 * ����  ����
 * ���  ����
 * ע��  ����
 ************************************************/
void VSYNC_Init(void)
{
    VSYNC_GPIO_Configuration();
    VSYNC_EXTI_Configuration();
    VSYNC_NVIC_Configuration();
}

/************************************************
 * ��������Sensor_Init
 * ����  ��Sensor��ʼ��
 * ����  ����
 * ���  ������1�ɹ�������0ʧ��
 * ע��  ����
 ************************************************/
ErrorStatus Ov7725_Init(void)
{
	uint16_t i = 0;
	uint8_t Sensor_IDCode = 0;	
	
	//DEBUG("ov7725 Register Config Start......");
	
	if( 0 == SCCB_WriteByte ( 0x12, 0x80 ) ) /*��λsensor */
	{
		//DEBUG("sccb write data error");		
		return ERROR ;
	}	

	if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, 0x0b ) )	 /* ��ȡsensor ID��*/
	{
		//DEBUG("read id faild");		
		return ERROR;
	}
	//DEBUG("Sensor ID is 0x%x", Sensor_IDCode);	
	
	if(Sensor_IDCode == OV7725_ID)
	{
		for( i = 0 ; i < OV7725_REG_NUM ; i++ )
		{
			if( 0 == SCCB_WriteByte(Sensor_Config[i].Address, Sensor_Config[i].Value) )
			{                
				//DEBUG("write reg faild", Sensor_Config[i].Address);
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}
	//DEBUG("ov7725 Register Config Success");
	
	return SUCCESS;
}

void DisableCamera(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  EXTI_InitTypeDef EXTI_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	
		SCL_H;
		SDA_H;		
	    						
    EXTI_InitStructure.EXTI_Line = macOV7725_VSYNC_EXTI_LINE;
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
	
    NVIC_InitStructure.NVIC_IRQChannel = macOV7725_VSYNC_EXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		FIFO_WRST_L();
		FIFO_RRST_L();
		FIFO_RCLK_H();			  				
    FIFO_WE_H(); 
		FIFO_CS_H();
	
		/*PB8-PB15(FIFO_DATA--FIFO�������)*/
		macOV7725_DATA_SCK_APBxClock_FUN ( macOV7725_DATA_GPIO_CLK, ENABLE );
		GPIO_InitStructure.GPIO_Pin = macOV7725_DATA_0_GPIO_PIN | macOV7725_DATA_1_GPIO_PIN | macOV7725_DATA_2_GPIO_PIN | macOV7725_DATA_3_GPIO_PIN |
		                              macOV7725_DATA_4_GPIO_PIN | macOV7725_DATA_5_GPIO_PIN | macOV7725_DATA_6_GPIO_PIN | macOV7725_DATA_7_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_Init(macOV7725_DATA_GPIO_PORT, &GPIO_InitStructure);
		
		macOV7725_VSYNC_SCK_APBxClock_FUN ( macOV7725_VSYNC_GPIO_CLK, ENABLE );	  /*PA0---VSYNC*/
    GPIO_InitStructure.GPIO_Pin =  macOV7725_VSYNC_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(macOV7725_VSYNC_GPIO_PORT, &GPIO_InitStructure);
}

/*�������OV7725�������ɼ��ϵ�����*/

/**
  * @brief  ���ù���ģʽ
  * @param  mode :����ģʽ��������Χ[0~5]
			@arg 0:�Զ�
			@arg 1:����
			@arg 2:����
			@arg 3:�칫��
			@arg 4:����
			@arg 5:ҹ��
  * @retval ��
  */
void OV7725_Light_Mode(uint8_t mode)
{
	switch(mode)
	{
		case 0:	//Auto���Զ�ģʽ
			SCCB_WriteByte(0x13, 0xff); //AWB on 
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;
		case 1://sunny������
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x5a);
			SCCB_WriteByte(0x02, 0x5c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 2://cloudy������
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x58);
			SCCB_WriteByte(0x02, 0x60);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 3://office���칫��
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x84);
			SCCB_WriteByte(0x02, 0x4c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 4://home������
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x96);
			SCCB_WriteByte(0x02, 0x40);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		
		case 5://night��ҹ��
			SCCB_WriteByte(0x13, 0xff); //AWB on
			SCCB_WriteByte(0x0e, 0xe5);
			break;	
		
		default:
			 ; 

			break;
	}

}			


/**
  * @brief  ���ñ��Ͷ�
  * @param  sat:���Ͷ�,������Χ[-4 ~ +4]             	
  * @retval ��
  */
void OV7725_Color_Saturation(int8_t sat)
{

 	if(sat >=-4 && sat<=4)
	{	
		SCCB_WriteByte(USAT, (sat+4)<<4); 
		SCCB_WriteByte(VSAT, (sat+4)<<4);
	}
	else
	{
		;
	}
	
}			


/**
  * @brief  ���ù��ն�
	* @param  bri:���նȣ�������Χ[-4~+4]
  * @retval ��
  */
void OV7725_Brightness(int8_t bri)
{
	uint8_t BRIGHT_Value,SIGN_Value;	
	
	switch(bri)
	{
		case 4:
				BRIGHT_Value = 0x48;
				SIGN_Value = 0x06;
			break;
		
		case 3:
				BRIGHT_Value = 0x38;
				SIGN_Value = 0x06;		
		break;	
		
		case 2:
				BRIGHT_Value = 0x28;
				SIGN_Value = 0x06;			
		break;	
		
		case 1:
				BRIGHT_Value = 0x18;
				SIGN_Value = 0x06;			
		break;	
		
		case 0:
				BRIGHT_Value = 0x08;
				SIGN_Value = 0x06;			
		break;	
		
		case -1:
				BRIGHT_Value = 0x08;
				SIGN_Value = 0x0e;		
		break;	
		
		case -2:
				BRIGHT_Value = 0x18;
				SIGN_Value = 0x0e;		
		break;	
		
		case -3:
				BRIGHT_Value = 0x28;
				SIGN_Value = 0x0e;		
		break;	
		
		case -4:
				BRIGHT_Value = 0x38;
				SIGN_Value = 0x0e;		
		break;	
		
		default:
			;
			break;
	}

		SCCB_WriteByte(BRIGHT, BRIGHT_Value); //AWB on
		SCCB_WriteByte(SIGN, SIGN_Value);
}		

/**
  * @brief  ���öԱȶ�
	* @param  cnst:�Աȶȣ�������Χ[-4~+4]
  * @retval ��
  */
void OV7725_Contrast(int8_t cnst)
{
	if(cnst >= -4 && cnst <=4)
	{
		SCCB_WriteByte(CNST, (0x30-(4-cnst)*4));
	}
	else
	{
		;
	}
}		


/**
  * @brief  ��������Ч��
	* @param  eff:����Ч����������Χ[0~6]:
			@arg 0:����
			@arg 1:�ڰ�
			@arg 2:ƫ��
			@arg 3:����
			@arg 4:ƫ��
			@arg 5:ƫ��
			@arg 6:����
  * @retval ��
  */
void OV7725_Special_Effect(uint8_t eff)
{
	switch(eff)
	{
		case 0://����
			SCCB_WriteByte(0xa6, 0x06);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0x80);
		break;
		
		case 1://�ڰ�
			SCCB_WriteByte(0xa6, 0x26);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0x80);
		break;	
		
		case 2://ƫ��
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0xa0);
			SCCB_WriteByte(0x61, 0x40);	
		break;	
		
		case 3://����
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x40);
			SCCB_WriteByte(0x61, 0xa0);	
		break;	
		
		case 4://ƫ��
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0xc0);		
		break;	
		
		case 5://ƫ��
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x60);
			SCCB_WriteByte(0x61, 0x60);		
		break;	
		
		case 6://����
			SCCB_WriteByte(0xa6, 0x46);
		break;	
				
		default:
			;
			break;
	}
}		



/**
  * @brief  ����ͼ��������ڣ��ֱ��ʣ�QVGA
	* @param  sx:����x��ʼλ��
	* @param  sy:����y��ʼλ��
	* @param  width:���ڿ��
	* @param  height:���ڸ߶�
	* @param QVGA_VGA:0,QVGAģʽ��1��VGAģʽ
  *
	* @note 	QVGAģʽ ����Ҫ��sx + width <= 320 ,sy+height <= 240
	* 			 	VGAģʽ����Ҫ��sx + width <= 640 ,sy+height <= 480
	*					������ Һ�����ֱ��� �� FIFO�ռ� �����ƣ������̲������ڳ���320*240������
	*         ʹ��VGAģʽ��Ҫ����ΪOV7725�޷�ֱ�ӽ���XY����QVGA������ʹ����ƽ��ʾ��
	*					���ó�VGAģʽ������ʹ��������ʾ��
	*					���QVGAģʽ��ͬ���ֱ����� VGAģʽ ͼ�����֡������
  * @retval ��
  */
void OV7725_Window_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height,uint8_t QVGA_VGA)
{
	uint8_t reg_raw,cal_temp;

	/***********QVGA or VGA *************/
	if(QVGA_VGA == 0)
	{
		/*QVGA RGB565 */
		SCCB_WriteByte(COM7,0x46); 
	}
	else
	{
			/*VGA RGB565 */
		SCCB_WriteByte(COM7,0x06); 
	}

	/***************HSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�HStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,HSTART);
	
	//sxΪ����ƫ�ƣ���8λ�洢��HSTART����2λ��HREF
	cal_temp = (reg_raw + (sx>>2));	
	SCCB_WriteByte(HSTART,cal_temp ); 
	
	/***************HSIZE*********************/
	//ˮƽ��ȣ���8λ�洢��HSIZE����2λ�洢��HREF
	SCCB_WriteByte(HSIZE,width>>2);//HSIZE������λ 
	
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�VStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,VSTART);	
	//syΪ����ƫ�ƣ���8λ�洢��HSTART����1λ��HREF
	cal_temp = (reg_raw + (sy>>1));	
	
	SCCB_WriteByte(VSTART,cal_temp);
	
	/***************VSIZE*********************/
	//��ֱ�߶ȣ���8λ�洢��VSIZE����1λ�洢��HREF
	SCCB_WriteByte(VSIZE,height>>1);//VSIZE����һλ
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,HREF);	
	//��ˮƽ��ȵĵ�2λ����ֱ�߶ȵĵ�1λ��ˮƽƫ�Ƶĵ�2λ����ֱƫ�Ƶĵ�1λ��������ӵ�HREF
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2)|((sx&0x03)<<4)|((sy&0x01)<<6));	
	
	SCCB_WriteByte(HREF,cal_temp);
	
	/***************HOUTSIZIE /VOUTSIZE*********************/
	SCCB_WriteByte(HOutSize,width>>2);
	SCCB_WriteByte(VOutSize,height>>1);
	
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,EXHCH);	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2));	

	SCCB_WriteByte(EXHCH,cal_temp);	
}


/**
  * @brief  ����ͼ��������ڣ��ֱ��ʣ�VGA
	* @param  sx:����x��ʼλ��
	* @param  sy:����y��ʼλ��
	* @param  width:���ڿ��
	* @param  height:���ڸ߶�
	* @note 	����������Ҫ��sx + width <= 640 ,sy+height <= 480
	*					������ Һ�����ֱ��� �� FIFO�ռ� �����ƣ������̲������ڳ���320*240������
	*         ʹ�ñ�������Ҫ����ΪOV7725�޷�ֱ�ӽ���XY����QVGA������ʹ����ƽ��ʾ��
	*					ʹ�ñ��������ó�VGAģʽ������ʹ��������ʾ��
	*					���QVGAģʽ��ͬ���ֱ����� VGAģʽ ͼ�����֡������
  * @retval ��
  */
void OV7725_Window_VGA_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	
	uint8_t reg_raw,cal_temp;

	/***********QVGA or VGA *************/
	/*VGA RGB565 */
	SCCB_WriteByte(COM7,0x06); 

	/***************HSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�HStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,HSTART);
	
	//sxΪ����ƫ�ƣ���8λ�洢��HSTART����2λ��HREF
	cal_temp = (reg_raw + (sx>>2));	
	SCCB_WriteByte(HSTART,cal_temp ); 
	
	/***************HSIZE*********************/
	//ˮƽ��ȣ���8λ�洢��HSIZE����2λ�洢��HREF
	SCCB_WriteByte(HSIZE,width>>2);//HSIZE������λ 320 
	
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�VStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	SCCB_ReadByte(&reg_raw,1,VSTART);	
	//syΪ����ƫ�ƣ���8λ�洢��HSTART����1λ��HREF
	cal_temp = (reg_raw + (sy>>1));	
	
	SCCB_WriteByte(VSTART,cal_temp);
	
	/***************VSIZE*********************/
	//��ֱ�߶ȣ���8λ�洢��VSIZE����1λ�洢��HREF
	SCCB_WriteByte(VSIZE,height>>1);//VSIZE����һλ 240
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,HREF);	
	//��ˮƽ��ȵĵ�2λ����ֱ�߶ȵĵ�1λ��ˮƽƫ�Ƶĵ�2λ����ֱƫ�Ƶĵ�1λ��������ӵ�HREF
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2)|((sx&0x03)<<4)|((sy&0x01)<<6));	
	
	SCCB_WriteByte(VSTART,cal_temp);
	
	/***************HOUTSIZIE /VOUTSIZE*********************/
	SCCB_WriteByte(HOutSize,width>>2);
	SCCB_WriteByte(VOutSize,height>>1);
	
	//��ȡ�Ĵ�����ԭ����	
	SCCB_ReadByte(&reg_raw,1,EXHCH);	
	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2));	

	SCCB_WriteByte(EXHCH,cal_temp);	
}

/**
  * @brief  ������ʾλ��
	* @param  sx:x��ʼ��ʾλ��
	* @param  sy:y��ʼ��ʾλ��
	* @param  width:��ʾ���ڿ��,Ҫ���OV7725_Window_Set�����е�widthһ��
	* @param  height:��ʾ���ڸ߶ȣ�Ҫ���OV7725_Window_Set�����е�heightһ��
  * @retval ��
  */
void ImagDisp(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	uint16_t i, j; 
	uint16_t Camera_Data;
	
	ILI9341_OpenWindow(sx,sy,width,height);
	ILI9341_Write_Cmd ( CMD_SetPixel );	

	for(i = 0; i < width; i++)
	{
		for(j = 0; j < height; j++)
		{
			READ_FIFO_PIXEL(Camera_Data);		/* ��FIFO����һ��rgb565���ص�Camera_Data���� */
			ILI9341_Write_Data(Camera_Data);
		}
	}
}




/****************************End OF File*************************************/

