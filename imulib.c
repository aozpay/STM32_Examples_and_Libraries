#include "imulib.h"
#include "stm32f3xx_hal.h"
extern MEMS_HandleTypeDef mems;
extern HAL_StatusTypeDef status;
uint8_t register_value = 0; 
uint8_t idcontrolvalue = 0;
uint8_t mems_acc_xyz_buffer[6];
uint8_t mems_mag_xyz_buffer[6];
uint8_t mems_gyro_xyz_buffer[6];
uint8_t txbufferwrite[2];
uint8_t txbufferread[2];
uint8_t receivedbyte=0;
uint8_t value = 0;


void Error(void)
	{
		if(status != HAL_OK)
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	}
void Success(void)
	{
		if(status == HAL_OK)
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	}
HAL_StatusTypeDef MEMS_Init_Control(MEMS_HandleTypeDef *mems)
	{
		if(mems==NULL)
			{
				Error(); // Error();
				HAL_Delay(100);	
				return HAL_ERROR;
			}
		else
		{
			Success();
			return HAL_OK;
		}
	}
	
void MEMS_I2C_Write(uint8_t Addr,uint8_t Reg,uint8_t Value) // MEMS I2C BUS WRITING FUNCTIONS
	{
		status = HAL_I2C_Mem_Write(&hi2c1, (uint8_t)Addr, (uint8_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x100);
	}
	
	
uint8_t MEMS_I2C_ReadID(uint16_t Addr)
	{
	idcontrolvalue = MEMS_I2C_Read(Addr,0x0F);
	return idcontrolvalue;
	}

uint8_t MEMS_I2C_Read(uint16_t Addr,uint8_t Reg) // MEMS I2C BUS READING FUNCTIONS
	{
		status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x100);
		if(status != HAL_OK)
			Error();
		else if (status == HAL_OK)
				Success();	
			return value;
	}

void Mems_acc_getxyz(int16_t* pData)
{
if(MEMS_I2C_ReadID(MEMS_ACC_READ)==MEMS_ACC_READ)// Reading ID
		{
	uint8_t i=0;
	mems_acc_xyz_buffer[0] = MEMS_I2C_Read(MEMS_ACC_READ,OUT_X_L_A);
	mems_acc_xyz_buffer[1] = MEMS_I2C_Read(MEMS_ACC_READ,OUT_X_H_A);
	mems_acc_xyz_buffer[2] = MEMS_I2C_Read(MEMS_ACC_READ,OUT_Y_L_A);
	mems_acc_xyz_buffer[3] = MEMS_I2C_Read(MEMS_ACC_READ,OUT_Y_H_A);
	mems_acc_xyz_buffer[4] = MEMS_I2C_Read(MEMS_ACC_READ,OUT_Z_L_A);
	mems_acc_xyz_buffer[5] = MEMS_I2C_Read(MEMS_ACC_READ,OUT_Z_H_A);
	for(i=0;i<3;i++)
	{
		pData[i]=((int16_t)((uint8_t)mems_acc_xyz_buffer[2*i+1]<<8)+mems_acc_xyz_buffer[2*i]);
	}
}
}	
void Mems_mag_getxyz(int16_t* mData)
{
	if(MEMS_I2C_ReadID(MEMS_MAG_READ)==MAG_ID)
	{
		uint8_t i=0;
		mems_mag_xyz_buffer[0] = MEMS_I2C_Read(MEMS_MAG_READ,OUT_X_L_M);
		mems_mag_xyz_buffer[1] = MEMS_I2C_Read(MEMS_MAG_READ,OUT_X_H_M);
		mems_mag_xyz_buffer[2] = MEMS_I2C_Read(MEMS_MAG_READ,OUT_Y_L_M);
		mems_mag_xyz_buffer[3] = MEMS_I2C_Read(MEMS_MAG_READ,OUT_Y_H_M);
		mems_mag_xyz_buffer[4] = MEMS_I2C_Read(MEMS_MAG_READ,OUT_Z_L_M);
		mems_mag_xyz_buffer[5] = MEMS_I2C_Read(MEMS_MAG_READ,OUT_Z_H_M);
		for(i=0;i<3;i++)
	{
		mData[i]=((int16_t)((uint8_t)mems_mag_xyz_buffer[2*i+1]<<8)+mems_mag_xyz_buffer[2*i]);
	}
	}	
}
void Mems_gyro_getxyz(int16_t* gData)
{
	uint8_t i=0;
	mems_gyro_xyz_buffer[0] = MEMS_GYRO_SPI_Read(OUT_X_L_G);
	mems_gyro_xyz_buffer[1] = MEMS_GYRO_SPI_Read(OUT_X_H_G);
	mems_gyro_xyz_buffer[2] = MEMS_GYRO_SPI_Read(OUT_Y_L_G);
	mems_gyro_xyz_buffer[3] = MEMS_GYRO_SPI_Read(OUT_Y_H_G);
	mems_gyro_xyz_buffer[4] = MEMS_GYRO_SPI_Read(OUT_Z_L_G);
	mems_gyro_xyz_buffer[5] = MEMS_GYRO_SPI_Read(OUT_Z_H_G);
		for(i=0;i<3;i++)
	{
	gData[i]=((int16_t)((uint8_t)mems_gyro_xyz_buffer[2*i+1]<<8)+mems_gyro_xyz_buffer[2*i]);
	}
}
void MEMS_GYRO_SPI_Write(uint8_t Address,uint8_t Data)
{
	CS_ON;
	txbufferwrite[0] = Address;
	txbufferwrite[1] = Data;
	HAL_SPI_Transmit(&hspi1,txbufferwrite,2,0x1000);
	CS_OFF;
	
}	
uint8_t MEMS_GYRO_SPI_Read(uint8_t Address)
{		
		CS_ON;
		txbufferread[0] = Address|GYRO_Write_Cmd;
		HAL_SPI_Transmit(&hspi1,txbufferread,1,0x1000);
		HAL_SPI_Receive(&hspi1,&receivedbyte,1,0x1000);
	  CS_OFF;
	  return receivedbyte;
}
uint8_t MEMS_GYRO_ReadID(uint8_t Address)
{	
	return MEMS_GYRO_SPI_Read(Address);
}
	/*INIT*/
void MEMS_Init(void)
{
	MEMS_Init_Control(&mems);
	if(MEMS_Init_Control(&mems)== HAL_OK)
	{
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET);
	mems.Init.Axes			  	= ACC_Axes_Enable_Active;
	mems.Init.DataRate			= ACC_Date_Rate_200HZ;
	mems.Init.Power  			= ACC_Low_Power_Mod_DeActive;
	mems.Init.Resolution  		= ACC_High_Resolution_Active;	
	mems.Init.Scale			    = ACC_SCALE_2G;
  mems.Init.BlockData		    = ACC_Block_Data_DeActive;
	mems.Init.Big_Little_Endian = ACC_Little_Endian;
		
		
	mems.Init1.DataRate = MAG_DATA_RATE_220;
	mems.Init1.Temp			= MAG_TEMPERATURE_ACTIVE;
	mems.Init1.Gain			= MAG_GAIN_1_3;		
	mems.Init1.OperationMode = MAG_MODE_SELECT_CONTINUOUS;
		
		
  mems.Init2.Axes 								 = GYRO_AXES_ACTIVE;
	mems.Init2.PowerDownMode 				 = GYRO_POWER_NORMAL;
	mems.Init2.Bandwith 						 = GYRO_BANDWITH_DATA_RATE;
	mems.Init2.DataRate 						 = GYRO_OUT_DATA_RATE;
	mems.Init2.HighPassFilter 			 = GYRO_HIGH_PASS_FILTER_NORMAL2;
  mems.Init2.HighPassFilterCutOff  = GYRO_HIGH_PASS_FILTER_CUT_OFF;
	mems.Init2.SpiModeSelection			 = GYRO_SPI_MODE_4_WIRE;
	mems.Init2.Scale							   = GYRO_SCALE_500;
	mems.Init2.BigLittleEndian       = GYRO_LITTLE_ENDIAN;
	mems.Init2.BlockDataUpdate		   = GYRO_BLOCK_DATA_UPDATE_CONTINUOUS;
  mems.Init2.Rebootmemory				   = GYRO_REBOOT_MEMORY_NORMAL;
	mems.Init2.Fifo 								 = GYRO_FIFO_DEACTIVE;
	mems.Init2.HighPassFilterEnabled = GYRO_HIGH_PASS_FILTER_ACTIVE;
	mems.Init2.Int1 								 = GYRO_INT1_SELECTION;
	mems.Init2.OutSel 							 = GYRO_OUT_SELECTION;
		
	mems.Acc_reg_datas.Ctrl_reg1_a |= (uint8_t)(mems.Init.Power|mems.Init.DataRate|mems.Init.Axes);
	mems.Acc_reg_datas.Ctrl_reg4_a |= (uint8_t)(mems.Init.Resolution|mems.Init.Scale|mems.Init.BlockData|mems.Init.Big_Little_Endian);
	
	mems.Mag_reg_datas.Cra_reg_m 	 |= (uint8_t)(mems.Init1.DataRate|mems.Init1.Temp);
  mems.Mag_reg_datas.Crb_reg_m   |= (uint8_t)(mems.Init1.Gain);
  mems.Mag_reg_datas.Mr_reg_m    |= (uint8_t)(mems.Init1.OperationMode);
	
	mems.Gyro_reg_datas.Ctrl_reg1  |= (uint8_t)(mems.Init2.Axes|mems.Init2.PowerDownMode|mems.Init2.Bandwith|mems.Init2.DataRate);
	mems.Gyro_reg_datas.Ctrl_reg2  |= (uint8_t)(mems.Init2.HighPassFilterCutOff|mems.Init2.HighPassFilter);
	mems.Gyro_reg_datas.Ctrl_reg4  |= (uint8_t)(mems.Init2.SpiModeSelection|mems.Init2.Scale|mems.Init2.BlockDataUpdate);
	mems.Gyro_reg_datas.Ctrl_reg5  |= (uint8_t)(mems.Init2.OutSel|mems.Init2.Int1|mems.Init2.HighPassFilterEnabled|mems.Init2.Fifo|
																			mems.Init2.Rebootmemory);
																			
  if(MEMS_GYRO_ReadID(GYRO_WHO_AM_I) == GYRO_ID)
	{
			MEMS_GYRO_SPI_Write(CTRL_REG1_G,mems.Gyro_reg_datas.Ctrl_reg1);
		  HAL_Delay(10);
			MEMS_GYRO_SPI_Write(CTRL_REG2_G,mems.Gyro_reg_datas.Ctrl_reg2);
		  HAL_Delay(10);
			MEMS_GYRO_SPI_Write(CTRL_REG4_G,mems.Gyro_reg_datas.Ctrl_reg4);
		  HAL_Delay(10);
			MEMS_GYRO_SPI_Write(CTRL_REG5_G,mems.Gyro_reg_datas.Ctrl_reg5);
		  HAL_Delay(10);
		  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET);
	}		
	if(MEMS_I2C_ReadID(MEMS_ACC_READ)==ACC_ID)// Reading ID
		{
			//CTRL_REGISTER DATAS IS UPDATED.
			MEMS_I2C_Write(MEMS_ACC_WRITE,CTRL_REG1_A,mems.Acc_reg_datas.Ctrl_reg1_a); 
			HAL_Delay(10);
			MEMS_I2C_Write(MEMS_ACC_WRITE,CTRL_REG4_A,mems.Acc_reg_datas.Ctrl_reg4_a); 
			HAL_Delay(10);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
		}
	if(MEMS_I2C_ReadID(MEMS_MAG_READ)==MAG_ID)
		{
		 MEMS_I2C_Write(MEMS_MAG_WRITE,CRA_REG_M,mems.Mag_reg_datas.Cra_reg_m);
		 HAL_Delay(10);
		 MEMS_I2C_Write(MEMS_MAG_WRITE,CRB_REG_M,mems.Mag_reg_datas.Crb_reg_m);
		 HAL_Delay(10);
		 MEMS_I2C_Write(MEMS_MAG_WRITE,MR_REG_M,mems.Mag_reg_datas.Mr_reg_m);	
		 HAL_Delay(10);
		 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET);
		}
	}
 }


