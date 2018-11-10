#ifndef __IMULIB_H__
#define __IMULIB_H__


#ifdef __cplusplus
	extern "C"{
#endif


#include "stm32f3xx_hal.h"
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
//#define READWRITE_CMD ((uint8_t)0x80) // 1000 0000
//#define MULTIPLEBYTE_CMD ((uint8_t)0x40) // 0100 0000
#define CS_ON HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET)
#define CS_OFF HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET)
//#define DUMMY_BYTE	((uint8_t)0x00)

/* REGISTER MAPS */
#define CTRL_REG1_A 0x20
#define CTRL_REG4_A 0x23

#define CRA_REG_M 0x00
#define CRB_REG_M 0x01
#define MR_REG_M  0X02

#define MEMS_ACC_READ 0x33
#define MEMS_ACC_WRITE 0x32
#define MEMS_MAG_READ 0x3D
#define MEMS_MAG_WRITE 0x3C

#define CTRL_REG1_G 0x20
#define CTRL_REG2_G 0x21
#define CTRL_REG4_G 0x23
#define CTRL_REG5_G 0x24


#define ACC_ID 0x33
#define MAG_ID 0x3C
#define GYRO_ID 0xD4



/*CTRL1_REG1_DATAS*/
#define ACC_Low_Power_Mod_Active 	      (uint8_t)0x01 << 2
#define ACC_Low_Power_Mod_DeActive      (uint8_t)0x00 
#define ACC_Axes_Enable_Active          (uint8_t)0x07
#define ACC_Axes_Enable_DeActive        (uint8_t)0x00
#define ACC_Date_Rate_Power_Down_Mode   (uint8_t)0x00
#define ACC_Date_Rate_1HZ               (uint8_t)0x01<<4 // Date rate means ODR bits.Shifted 4 bits to left.Bacuse The ODR bits are 5,6,7,8. bits.
																						             // For examples 0x01 == 0000 0001 , Shifted 4 bits to left -> 0001 0000
#define ACC_Date_Rate_10HZ              (uint8_t)0x02<<4
#define ACC_Date_Rate_25HZ              (uint8_t)0x03<<4
#define ACC_Date_Rate_50HZ              (uint8_t)0x04<<4
#define ACC_Date_Rate_100HZ             (uint8_t)0x05<<4
#define	ACC_Date_Rate_200HZ             (uint8_t)0x06<<4
#define	ACC_Date_Rate_400HZ             (uint8_t)0x07<<4
#define	ACC_Date_Rate_1620HZ            (uint8_t)0x08<<4	// ONLY LOW POWER
#define	ACC_Date_Rate_1344HZ            (uint8_t)0x09<<4 // NORMAL MOD (1334 HZ) , LOW-POWER MODE (5376HZ)


/*CTRL_REG4_DATAS*/
#define ACC_SCALE_2G 	               (uint8_t)0x00
#define ACC_SCALE_4G 	         			 (uint8_t)0X01<<4
#define ACC_SCALE_8G 	         			 (uint8_t)0x02<<4
#define ACC_SCALE_16G					 	     (uint8_t)0x03<<4
#define ACC_Block_Data_Active        (uint8_t)0X01<<6
#define ACC_Block_Data_DeActive      (uint8_t)0x00
#define ACC_Little_Endian 		 			 (uint8_t)0x00
#define ACC_Little_Big_Endian  			 (uint8_t)0x01<<7
#define ACC_High_Resolution_Active   (uint8_t)0x01<<3
#define ACC_High_Resolution_DeActive (uint8_t)(0x00)


/*MEMS ACC X,Y,Z*/
#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D

//////////////////////////////////////////////////////////////////////////////////

/*CRA_REG_M DATAS*/
#define MAG_DATA_RATE_075 	(uint8_t)0x00<<2
#define MAG_DATA_RATE_1_5 	(uint8_t)0X01<<2 // 1.5 HZ
#define MAG_DATA_RATE_3   	(uint8_t)0X02<<2
#define MAG_DATA_RATE_7_5 	(uint8_t)0x03<<2 // 7.5 HZ
#define MAG_DATA_RATE_15  	(uint8_t)0x04<<2
#define MAG_DATA_RATE_30  	(uint8_t)0x05<<2
#define MAG_DATA_RATE_75  	(uint8_t)0x06<<2
#define MAG_DATA_RATE_220 	(uint8_t)0X07<<2
#define MAG_TEMPERATURE_ACTIVE	(uint8_t)0x01<<7
#define MAG_TEMPERATURE_DEACTIVE(uint8_t)0x00

/*CRB_REG_M*/
#define MAG_GAIN_1_3 (uint8_t)0X01<<5 // LSB/Gauss X,Y 1100 , Z 980	
#define MAG_GAIN_1_9 (uint8_t)0X02<<5 // LSB/Gauss X,Y 855  , Z 760  
#define MAG_GAIN_2_5 (uint8_t)0X03<<5 // LSB/Gauss X,Y 670  , Z 600
#define MAG_GAIN_4	 (uint8_t)0X04<<5 // LSB/Gauss X,Y 450  , Z 400
#define MAG_GAIN_4_7 (uint8_t)0X05<<5 // LSB/Gauss X,Y 400  , Z 355
#define MAG_GAIN_5_6 (uint8_t)0X06<<5 // LSB/Gauss X,Y 330  , Z 295
#define MAG_GAIN_8_1 (uint8_t)0X07<<5 // LSB/Gauss X,Y 230  , Z 205

/*MR_REG_M*/
#define MAG_MODE_SELECT_CONTINUOUS (uint8_t)0x00
#define MAG_MODE_SELECT_SINGLE_CONVERSION (uint8_t)0x01
#define MAG_MODE_SLEEP (uint8_t)0x02 

/*MEMS MAG X,Y,Z*/
#define OUT_X_H_M 0x03
#define OUT_X_L_M 0x04
#define OUT_Z_H_M 0x05
#define OUT_Z_L_M 0x06
#define OUT_Y_H_M 0x07
#define OUT_Y_L_M 0x08

/* GYROSCOPE*/////////////////////////
/*CTRL_REG1*/

#define GYRO_WHO_AM_I 0xF
#define GYRO_OUT_DATA_RATE (uint8_t)0x01<<6
#define GYRO_BANDWITH_DATA_RATE (uint8_t)0x03<<4
#define GYRO_AXES_ACTIVE (uint8_t)0x07
#define GYRO_AXES_DEACTIVE 0x00
#define GYRO_POWER_DOWN_ACTIVE 0x00
#define GYRO_POWER_NORMAL (uint8_t)0x01<<3

/*CTRL_REG2*/
#define GYRO_HIGH_PASS_FILTER_NORMAL1 0x00
#define GYRO_HIGH_PASS_FILTER_REFERENCE_SIGNAL (uint8_t)0x01 <<4
#define GYRO_HIGH_PASS_FILTER_NORMAL2 (uint8_t)0x02 << 4
#define GYRO_HIGH_PASS_FILTER_AUTORESET (uint8_t)0x03 << 4
#define GYRO_HIGH_PASS_FILTER_CUT_OFF 0x00


/*CTRL_REG4*/
#define GYRO_BLOCK_DATA_UPDATE_CONTINUOUS 0x00
#define GYRO_BLOCK_DATA_UPDATE_NOT_UPDATED (uint8_t)0x01<<7
#define GYRO_SCALE_250       (uint8_t)0x00
#define GYRO_SCALE_500       (uint8_t)0x01<<4
#define GYRO_SCALE_2000      (uint8_t)0x02<<4
#define GYRO_BIG_ENDIAN      (uint8_t)0x01<<6
#define GYRO_LITTLE_ENDIAN						0x00
#define GYRO_SPI_MODE_4_WIRE 					0x00
#define GYRO_SPI_MODE_3_WIRE (uint8_t)0x01

/*CTRL_REG5*/
#define GYRO_REBOOT_MEMORY_NORMAL             0x00
#define GYRO_REBOOT_MEMORY_REBOOT    (uint8_t)0x01<<7
#define GYRO_FIFO_ACTIVE             (uint8_t)0x01<<6
#define GYRO_FIFO_DEACTIVE                    0x00
#define GYRO_HIGH_PASS_FILTER_ACTIVE (uint8_t)0x01<<4
#define GYRO_HIGH_PASS_FILTER_DEACTIVE        0x00
#define GYRO_INT1_SELECTION                   0x00
#define GYRO_OUT_SELECTION                    0x00
 
/*MEMS GYRO X,Y,Z*/
#define OUT_X_L_G 0x28
#define OUT_X_H_G 0x29
#define OUT_Y_L_G 0x2A
#define OUT_Y_H_G 0x2B
#define OUT_Z_L_G 0x2C
#define OUT_Z_H_G 0x2D

/*GYRO WRITE CMD*/
#define GYRO_Write_Cmd 0x80

typedef	struct{
	uint8_t Power;
	uint8_t Axes;
	uint8_t Scale;
	uint8_t Resolution;
	uint8_t DataRate;
	uint8_t BlockData;
	uint8_t Big_Little_Endian;
}LSM303DLHCAcc_InitTypeDef;

typedef struct{
	uint8_t DataRate;
	uint8_t Temp;
	uint8_t Gain;	
	uint8_t OperationMode;
}LSM303DLHCMag_InitTypedef;

typedef struct{
	
	uint8_t DataRate;
	uint8_t Bandwith;
	uint8_t PowerDownMode;
	uint8_t Axes;
	uint8_t HighPassFilter;
	uint8_t HighPassFilterCutOff;
	uint8_t BlockDataUpdate;
	uint8_t BigLittleEndian;
	uint8_t Scale;
	uint8_t SpiModeSelection;
	uint8_t Rebootmemory;
	uint8_t Fifo;
	uint8_t HighPassFilterEnabled;
	uint8_t Int1;
	uint8_t OutSel;
}L3GD20Gyro_InitTypedef;



typedef struct{
	uint8_t Ctrl_reg1_a;
	uint8_t Ctrl_reg4_a;
}LSM303DLHCACC_Registers_Datas;


typedef struct{
	uint8_t Cra_reg_m;
	uint8_t Crb_reg_m;
	uint8_t Mr_reg_m;
}LSM303DLHCMag_Registers_Datas;


typedef struct{
	uint8_t Who_am_i;
	uint8_t Ctrl_reg1;
	uint8_t Ctrl_reg2;
	uint8_t Ctrl_reg4;
	uint8_t Ctrl_reg5;
}L3GD20Gyro_Register_Datas;
/*typedef struct{
	
}LSM303DLHCMag_InitTypeDef;
*/
typedef struct {
	LSM303DLHCAcc_InitTypeDef Init;
	LSM303DLHCMag_InitTypedef	Init1;
	L3GD20Gyro_InitTypedef    Init2;
	LSM303DLHCACC_Registers_Datas Acc_reg_datas;
	LSM303DLHCMag_Registers_Datas Mag_reg_datas;
	L3GD20Gyro_Register_Datas     Gyro_reg_datas;
}MEMS_HandleTypeDef;


/*FUNCTIONS PROTOTYPE*/

uint8_t MEMS_I2C_Read(uint16_t Addr,uint8_t Reg); // MEMS I2C BUS READING FUNCTIONS
void MEMS_I2C_Write(uint8_t I2C_Acc_Addr,uint8_t I2C_Acc_Reg,uint8_t I2C_Acc_Value); // MEMS I2C BUS WRITING FUNCTIONS
HAL_StatusTypeDef MEMS_Init_Control(MEMS_HandleTypeDef *mems);

uint8_t MEMS_I2C_ReadID(uint16_t Addr);
uint8_t MEMS_GYRO_ReadID(uint8_t Addr);

void MEMS_GYRO_SPI_Write(uint8_t Address,uint8_t Data);
uint8_t MEMS_GYRO_SPI_Read(uint8_t Address);

void MEMS_Init(void);
void Mems_acc_getxyz(int16_t* pData);
void Mems_mag_getxyz(int16_t* mData);
void Mems_gyro_getxyz(int16_t* gData);
void Error(void);
void Success(void);
#ifdef __cplusplus
}
#endif
#endif
