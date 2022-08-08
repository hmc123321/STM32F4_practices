#ifndef __ST7735_H__
#define __ST7735_H__

#include "main.h"

extern SPI_HandleTypeDef hspi1;

#define SPI_DC_0 HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET);
#define SPI_DC_1 HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_SET);
#define SPI_CS_0 HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,GPIO_PIN_RESET);
#define SPI_CS_1 HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,GPIO_PIN_SET);
#define SPI_RST_0 HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,GPIO_PIN_RESET);
#define SPI_RST_1 HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,GPIO_PIN_SET);
#define delay_ms(x) HAL_Delay(x);

//定义显示区域大小，偏移
#define TFT_COLUMN_NUMBER 160
#define TFT_LINE_NUMBER 80
#define TFT_COLUMN_OFFSET 0
#define TFT_LINE_OFFSET 24//25

//定义常用颜色
#define RED   0XF800
#define GREEN   0X07E0
#define BLUE  0X001F
#define PIC_LEN 120
#define PIC_HIG 80
#define PIC_NUMBER 28800

void SPI_SendByte(unsigned char byte);
void TFT_SEND_CMD(unsigned char o_command);
void TFT_SEND_DATA(unsigned char o_command);
void TFT_ADR_SET(void);
void TFT_clear(void);
void TFT_full(unsigned long color);
void TFT_init(void);
void display_char16_16(unsigned int x,unsigned int y,unsigned long color,const unsigned char *point);
void Picture_display(const uint8_t *ptr_pic,uint16_t len);
void Display_Buffer(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t *bitmap);
#endif

