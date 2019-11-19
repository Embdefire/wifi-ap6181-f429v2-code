
#include "./delay/core_delay.h"   
#include "bsp_ov5640.h"

int cur_index = 0;


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  TIMEOUT  2


/**
  * @brief  ��ʼ����������ͷʹ�õ�GPIO(I2C/DCMI)
  * @param  None
  * @retval None
  */
void OV5640_HW_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		I2C_InitTypeDef  I2C_InitStruct;

		/***DCMI��������***/
		/* ʹ��DCMIʱ�� */
		RCC_AHB1PeriphClockCmd(DCMI_PWDN_GPIO_CLK|DCMI_RST_GPIO_CLK|DCMI_VSYNC_GPIO_CLK | DCMI_HSYNC_GPIO_CLK | DCMI_PIXCLK_GPIO_CLK|
		DCMI_D0_GPIO_CLK| DCMI_D1_GPIO_CLK| DCMI_D2_GPIO_CLK| DCMI_D3_GPIO_CLK|
		DCMI_D4_GPIO_CLK| DCMI_D5_GPIO_CLK| DCMI_D6_GPIO_CLK| DCMI_D7_GPIO_CLK, ENABLE);

		/*����/ͬ���ź���*/
		GPIO_InitStructure.GPIO_Pin = DCMI_VSYNC_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
		GPIO_Init(DCMI_VSYNC_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_VSYNC_GPIO_PORT, DCMI_VSYNC_PINSOURCE, DCMI_VSYNC_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_HSYNC_GPIO_PIN ;
		GPIO_Init(DCMI_HSYNC_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_HSYNC_GPIO_PORT, DCMI_HSYNC_PINSOURCE, DCMI_HSYNC_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_PIXCLK_GPIO_PIN ;
		GPIO_Init(DCMI_PIXCLK_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_PIXCLK_GPIO_PORT, DCMI_PIXCLK_PINSOURCE, DCMI_PIXCLK_AF);

		/*�����ź�*/
		GPIO_InitStructure.GPIO_Pin = DCMI_D0_GPIO_PIN ;
		GPIO_Init(DCMI_D0_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D0_GPIO_PORT, DCMI_D0_PINSOURCE, DCMI_D0_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_D1_GPIO_PIN ;
		GPIO_Init(DCMI_D1_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D1_GPIO_PORT, DCMI_D1_PINSOURCE, DCMI_D1_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_D2_GPIO_PIN ;
		GPIO_Init(DCMI_D2_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D2_GPIO_PORT, DCMI_D2_PINSOURCE, DCMI_D2_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_D3_GPIO_PIN ;
		GPIO_Init(DCMI_D3_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D3_GPIO_PORT, DCMI_D3_PINSOURCE, DCMI_D3_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_D4_GPIO_PIN ;
		GPIO_Init(DCMI_D4_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D4_GPIO_PORT, DCMI_D4_PINSOURCE, DCMI_D4_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_D5_GPIO_PIN ;
		GPIO_Init(DCMI_D5_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D5_GPIO_PORT, DCMI_D5_PINSOURCE, DCMI_D5_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_D6_GPIO_PIN ;
		GPIO_Init(DCMI_D6_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D6_GPIO_PORT, DCMI_D6_PINSOURCE, DCMI_D6_AF);

		GPIO_InitStructure.GPIO_Pin = DCMI_D7_GPIO_PIN ;
		GPIO_Init(DCMI_D7_GPIO_PORT, &GPIO_InitStructure);
		GPIO_PinAFConfig(DCMI_D7_GPIO_PORT, DCMI_D7_PINSOURCE, DCMI_D7_AF);



		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = DCMI_PWDN_GPIO_PIN ;
		GPIO_Init(DCMI_PWDN_GPIO_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = DCMI_RST_GPIO_PIN ;
		GPIO_Init(DCMI_RST_GPIO_PORT, &GPIO_InitStructure);
		/*PWDN���ţ��ߵ�ƽ�رյ�Դ���͵�ƽ����*/

		GPIO_ResetBits(DCMI_RST_GPIO_PORT,DCMI_RST_GPIO_PIN);
		GPIO_SetBits(DCMI_PWDN_GPIO_PORT,DCMI_PWDN_GPIO_PIN);

		Delay(10);

		GPIO_ResetBits(DCMI_PWDN_GPIO_PORT,DCMI_PWDN_GPIO_PIN);

		Delay(10);

		GPIO_SetBits(DCMI_RST_GPIO_PORT,DCMI_RST_GPIO_PIN);


}

/**
  * @brief  Resets the OV5640 camera.
  * @param  None
  * @retval None
  */
void OV5640_Reset(void)
{
	/*OV5640�����λ*/
  OV5640_WriteReg(0x3008, 0x80);
}

/**
  * @brief  ��ȡ����ͷ��ID.
  * @param  OV5640ID: �洢ID�Ľṹ��
  * @retval None
  */
void OV5640_ReadID(OV5640_IDTypeDef *OV5640ID)
{

	/*��ȡ�Ĵ�оƬID*/
  OV5640ID->PIDH = OV5640_ReadReg(OV5640_SENSOR_PIDH);
  OV5640ID->PIDL = OV5640_ReadReg(OV5640_SENSOR_PIDL);
}


/**
  * @brief  дһ�ֽ����ݵ�OV5640�Ĵ���
  * @param  Addr: OV5640 �ļĴ�����ַ
  * @param  Data: Ҫд�������
  * @retval ����0��ʾд��������0xFF��ʾ����
  */
uint8_t OV5640_WriteReg(uint16_t Addr, uint8_t Data)
{
	uint32_t timeout = DCMI_TIMEOUT_MAX;
  
	/* Generate the Start Condition */
	I2C_GenerateSTART(CAMERA_I2C, ENABLE);

	/* Test on CAMERA_I2C EV5 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_MODE_SELECT))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	}
   
	/* Send DCMI selcted device slave Address for write */
	I2C_Send7bitAddress(CAMERA_I2C, OV5640_DEVICE_ADDRESS, I2C_Direction_Transmitter);
 
	/* Test on CAMERA_I2C EV6 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	}
 
	/* Send CAMERA_I2C location address MSB */
	I2C_SendData(CAMERA_I2C, (uint8_t)( (Addr >> 8) & 0xFF) );

	/* Test on CAMERA_I2C EV8 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	}
	//--------------------------------------------------------
	/* Send I2C1 location address LSB */
	I2C_SendData( CAMERA_I2C, (uint8_t)(Addr & 0xFF) );
	/* Test on I2C1 EV8 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	} 
  

	//--------------------------------------------------------

	/* Send Data */
	I2C_SendData(CAMERA_I2C, Data);    

	/* Test on CAMERA_I2C EV8 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	}  
 
	/* Send I2C1 STOP Condition */
	I2C_GenerateSTOP(CAMERA_I2C, ENABLE);
  
	/* If operation is OK, return 0 */
	return 0;
}
/**
  * @brief  ��OV5640�Ĵ����ж�ȡһ���ֽڵ�����
  * @param  Addr: �Ĵ�����ַ
  * @retval ���ض�ȡ�õ�����
  */
uint8_t OV5640_ReadReg(uint16_t Addr)
{
	uint32_t timeout = DCMI_TIMEOUT_MAX;
	uint8_t Data = 0;

	/* Generate the Start Condition */
	I2C_GenerateSTART(CAMERA_I2C, ENABLE);

	/* Test on CAMERA_I2C EV5 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_MODE_SELECT))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	} 
  
	/* Send DCMI selcted device slave Address for write */
	I2C_Send7bitAddress(CAMERA_I2C, OV5640_DEVICE_ADDRESS, I2C_Direction_Transmitter);
 
	/* Test on I2C1 EV6 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	} 

	/* Send I2C1 location address MSB */
	I2C_SendData( CAMERA_I2C, (uint8_t)((Addr>>8) & 0xFF) );

	/* Test on I2C1 EV8 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	} 
  
	/* Clear AF flag if arised */
	CAMERA_I2C->SR1 |= (uint16_t)0x0400; 
  
//--------------------------------------------------------
	/* Send I2C1 location address LSB */
	I2C_SendData( CAMERA_I2C, (uint8_t)(Addr & 0xFF) );
	/* Test on I2C1 EV8 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	} 
  
	/* Clear AF flag if arised */
	CAMERA_I2C->SR1 |= (uint16_t)0x0400;
	//--------------------------------------------------------

	/* Generate the Start Condition */
	I2C_GenerateSTART(CAMERA_I2C, ENABLE);
  
	/* Test on I2C1 EV6 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_MODE_SELECT))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	} 
  
	/* Send DCMI selcted device slave Address for write */
	I2C_Send7bitAddress(CAMERA_I2C, OV5640_DEVICE_ADDRESS, I2C_Direction_Receiver);
   
	/* Test on I2C1 EV6 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	}  
 
	/* Prepare an NACK for the next data received */
	I2C_AcknowledgeConfig(CAMERA_I2C, DISABLE);
	
	/* Test on I2C1 EV7 and clear it */
	timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
	while(!I2C_CheckEvent(CAMERA_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		/* If the timeout delay is exeeded, exit with error code */
		if ((timeout--) == 0) return 0xFF;
	}   
    
	/* Prepare Stop after receiving data */
	I2C_GenerateSTOP(CAMERA_I2C, ENABLE);

	/* Receive the Data */
	Data = I2C_ReceiveData(CAMERA_I2C);

	/* return the read data */
	return Data;
}


