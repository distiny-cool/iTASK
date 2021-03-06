#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"

//引脚定义
#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY1_GPIO_PORT    GPIOA			   
#define    KEY1_GPIO_PIN		 GPIO_Pin_0
#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY2_GPIO_PORT    GPIOC		   
#define    KEY2_GPIO_PIN		  GPIO_Pin_13
#define    KEY3_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY3_GPIO_PORT    GPIOC			   
#define    KEY3_GPIO_PIN		 GPIO_Pin_10

/*
按键按下标志宏3
按键按下为高电平，设置KEY_ON=1,KEY_OFF=0
*/
#define KEY_ON	1
#define KEY_OFF	0

void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif /* __KEY_H */

