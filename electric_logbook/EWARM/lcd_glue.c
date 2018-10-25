#include <stdint.h>
#include "main.h"
#include "stm32f0xx_hal.h"
#include "OS_glue.h"
#include "spi.h"

#define DEFAULT_SPI_BUSY_TIMEOUT	10000

static inline void lcd_cs_select(void)
{
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

static inline void lcd_cs_deselect(void)
{
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

static inline void lcd_reset(void)
{
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
}

static inline void lcd_nreset(void)
{
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
}

static inline void lcd_dc_command(void)
{
	HAL_GPIO_WritePin(LCD_DC_PIN_GPIO_Port, LCD_DC_PIN_Pin, GPIO_PIN_RESET);
}

static inline void lcd_dc_data(void)
{
	HAL_GPIO_WritePin(LCD_DC_PIN_GPIO_Port, LCD_DC_PIN_Pin, GPIO_PIN_SET);
}

void LCD_IO_Init(void)
{
	lcd_cs_select();
	Delay(100);
	lcd_reset();
	Delay(500);
	lcd_nreset();
	Delay(200);
	lcd_cs_deselect();
}

void LCD_IO_WriteData(uint16_t RegValue)
{
	lcd_cs_select();
    lcd_dc_data();
	HAL_SPI_Transmit(&hspi2, &RegValue, 2, DEFAULT_SPI_BUSY_TIMEOUT);
	lcd_cs_deselect();
}

void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size)
{
	lcd_cs_select();
	lcd_dc_data();
	HAL_SPI_Transmit(&hspi2, pData, Size, DEFAULT_SPI_BUSY_TIMEOUT);
	lcd_cs_deselect();
}

void LCD_IO_WriteReg(uint8_t Reg)
{
	lcd_cs_select();
	lcd_dc_command();
	HAL_SPI_Transmit(&hspi2, &Reg, 1, DEFAULT_SPI_BUSY_TIMEOUT);
	lcd_cs_deselect();

}

uint16_t LCD_IO_ReadData(uint16_t Reg)
{

}

void LCD_Delay (const uint32_t delay)
{
	Delay(delay);
}