#include "iic.h"

#include "delay.h"
#include "oled.h"
/**********************************************
//		GND -> GND
//		VCC -> VCC
//		SCL -> GPIOA11
//		SDA -> GPIOA12
**********************************************/

//初始化GPIO
void IIC2_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //使能GPIOA时钟
    
    //PH4,5初始化设置
    GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_12;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    IIC_SDA=1;
    IIC_SCL=1;
}

/* IIC读写函数 -------------------------------------*/
/* 慢速读写 ----------------------------------------*/
void IIC_WR_Byte(u8 dat, u8 cmd)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);
	IIC_Wait_Ack();	
	if(cmd)		// 数据
	{
		IIC_Send_Byte(OLED_DATA_CHR);
	}
	else		// 命令
	{
		IIC_Send_Byte(OLED_CMD_CHR);
	}
	IIC_Wait_Ack();
	IIC_Send_Byte(dat); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

void IIC_WR_Byte_Dat(u8 dat)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);
	IIC_Wait_Ack();	
	IIC_Send_Byte(OLED_DATA_CHR);
	IIC_Wait_Ack();
	IIC_Send_Byte(dat); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

void IIC_WR_Byte_Cmd(u8 dat)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_CMD_CHR);
	IIC_Wait_Ack();
	IIC_Send_Byte(dat); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

/* 快速读写 ----------------------------------------*/
void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	if(cmd)			// 数据
	{
		IIC_Send_Byte(OLED_DATA_CHR);
	}
	else			// 命令
	{
		IIC_Send_Byte(OLED_CMD_CHR);
	}
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*buf);
		IIC_Wait_Ack();
		buf++;
	}
	IIC_Stop();
}

void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_DATA_CHR);
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*buf);
		IIC_Wait_Ack();
		buf++;
	}
	IIC_Stop();
}

void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_CMD_CHR);
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*buf);
		IIC_Wait_Ack();
		buf++;
	}
	IIC_Stop();
}

/* IIC协议模块 -------------------------------------*/
#ifdef FAST_IIC_FOR_SSD1306
	#define SYSTEM_CORE_CLOCK (72000000)
	uint8_t	fac_hus=SYSTEM_CORE_CLOCK/1000000/2;  // 半us
	uint8_t	fac_125ns=SYSTEM_CORE_CLOCK/1000000/8;  // 125ns
	static void IIC_Fast_Delay_Hus(uint8_t Half_Us)
	{
		u32 ticks;
		u32 told,tnow,tcnt=0;
		u32 reload=SysTick->LOAD;				//LOAD的值	    	 
		ticks=Half_Us*fac_hus; 						//需要的节拍数 
		told=SysTick->VAL;        				//刚进入时的计数器值
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
				else tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
			}  
		};
	}
	static void IIC_Fast_Delay_125ns(uint8_t _125_Ns)
	{
		u32 ticks;
		u32 told,tnow,tcnt=0;
		u32 reload=SysTick->LOAD;				//LOAD的值	    	 
		ticks=_125_Ns*fac_125ns; 				//需要的节拍数 
		told=SysTick->VAL;        				//刚进入时的计数器值
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
				else tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
			}  
		};
	}
#endif /* FAST_IIC_FOR_SSD1306 */

static void IIC_Start(void)
{
	SDA_OUT();
	SDA_Clr();
	SCL_Clr();
	#ifdef FAST_IIC_FOR_SSD1306
		__NOP();
	#else
		delay_us(1);
	#endif
 	SDA_Set();
	#ifdef FAST_IIC_FOR_SSD1306
		__NOP();
	#else
		delay_us(1);
	#endif
	SCL_Set();
}

static void IIC_Stop(void)
{
	SDA_OUT();
	SCL_Set();
	SDA_Set();
	#ifdef FAST_IIC_FOR_SSD1306
		__NOP();
	#else
		delay_us(1);
	#endif
	SCL_Clr();
	SDA_Clr();
	#ifdef FAST_IIC_FOR_SSD1306
		__NOP();
	#else
		delay_us(1);
	#endif						   	
}

static u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();SDA_Clr();
	SCL_Clr();
	#ifdef FAST_IIC_FOR_SSD1306
		__NOP();
	#else
		delay_us(1);
	#endif
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL_Set();
	return 0;  
}

static void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    SCL_Set();
    for(t=0;t<8;t++)
    {              
        (txd&0x80) ? (SDA_Clr()) : (SDA_Set());
        txd<<=1;
		#ifdef FAST_IIC_FOR_SSD1306
			__NOP();
		#else
			delay_us(1);
		#endif
		SCL_Clr();
		#ifdef FAST_IIC_FOR_SSD1306
			__NOP();__NOP();__NOP();
			__NOP();__NOP();__NOP();
		#else
			delay_us(1);
		#endif
		SCL_Set();	
    }	 
}
