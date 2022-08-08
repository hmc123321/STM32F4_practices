#include "st7735.h"

void SPI_SendByte(unsigned char byte)
{
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&byte,1,0xFFFF);
}

void TFT_SEND_CMD(unsigned char o_command)
  {
		
    SPI_DC_0;
    SPI_CS_0;
    SPI_SendByte(o_command);
    SPI_CS_1;
	 
    //SPI_DC_1;
  }
void TFT_SEND_DATA(unsigned char o_data)
  { 
    SPI_DC_1;
    SPI_CS_0;
    SPI_SendByte(o_data);
    SPI_CS_1;
	  
   }
void  TFT_ADR_SET(void)
  {
	    TFT_SEND_CMD(0x2a);     //Column address set
  TFT_SEND_DATA(TFT_COLUMN_OFFSET>>8);    //start column
  TFT_SEND_DATA(TFT_COLUMN_OFFSET); 
  TFT_SEND_DATA((TFT_COLUMN_NUMBER -1+ TFT_COLUMN_OFFSET)>>8);    //end column
  TFT_SEND_DATA(TFT_COLUMN_NUMBER -1+ TFT_COLUMN_OFFSET);

  TFT_SEND_CMD(0x2b);     //Row address set
  TFT_SEND_DATA(TFT_LINE_OFFSET>>8);    //start row
  TFT_SEND_DATA(TFT_LINE_OFFSET); 
  TFT_SEND_DATA((TFT_LINE_NUMBER -1+ TFT_LINE_OFFSET)>>8);    //end row
  TFT_SEND_DATA(TFT_LINE_NUMBER -1 + TFT_LINE_OFFSET);
    TFT_SEND_CMD(0x2C);     //Memory write
  }
void TFT_clear(void)
  {
    unsigned int ROW,column;
	TFT_ADR_SET();
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
      { 
    
          for(column=0;column<TFT_COLUMN_NUMBER;column++)  //column loop
            {
        TFT_SEND_DATA(0x00);
        TFT_SEND_DATA(0x00);
            }
      }
  }
void TFT_full(unsigned long color)
  {
    unsigned int ROW,column;
    TFT_ADR_SET();
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
      { 
    
  for(column=0;column<TFT_COLUMN_NUMBER ;column++) //column loop
          {
        
        TFT_SEND_DATA(color>>8);
        TFT_SEND_DATA(color);
          }
      }
  }
void TFT_init(void)        ////GC9106
  {
  SPI_RST_0; 
  delay_ms(500);
  SPI_RST_1;
  delay_ms(500);				//RESET 
    TFT_SEND_CMD(0xfe);     //Inter register enable 1
    TFT_SEND_CMD(0xfe);     
    TFT_SEND_CMD(0xfe);
    TFT_SEND_CMD(0xef);     //Inter register enable 2

    TFT_SEND_CMD(0xb3);     //设置伽马调整允许
    TFT_SEND_DATA(0x03);
        
    TFT_SEND_CMD(0x36);     //Memory Access Ctrl
    TFT_SEND_DATA(0x68);        //MY MX MV ML BGR MH 0 0  竖屏D8 
        
    TFT_SEND_CMD(0x3a);             //Pixel Format Set
    TFT_SEND_DATA(0x05);            //16BIT  565格式

    TFT_SEND_CMD(0xb6);           //命令设置
    TFT_SEND_DATA(0x11);
    TFT_SEND_CMD(0xac);  
    TFT_SEND_DATA(0x0b);

    TFT_SEND_CMD(0xb4);             //Display Inversion Control
    TFT_SEND_DATA(0x21);

    TFT_SEND_CMD(0xb1);             //命令设置
    TFT_SEND_DATA(0xc0);

    TFT_SEND_CMD(0xe6);              //VREG1_CTL   
    TFT_SEND_DATA(0x50);
    TFT_SEND_DATA(0x43);	        //默认值
    TFT_SEND_CMD(0xe7);             //VREG2_CTL
    TFT_SEND_DATA(0x56);            //-3V
    TFT_SEND_DATA(0x43);	        //

    TFT_SEND_CMD(0xF0);             //SET_GAMMA1
    TFT_SEND_DATA(0x1f);
    TFT_SEND_DATA(0x41);
    TFT_SEND_DATA(0x1B);
    TFT_SEND_DATA(0x55);
    TFT_SEND_DATA(0x36);
    TFT_SEND_DATA(0x3d);
    TFT_SEND_DATA(0x3e);
    TFT_SEND_DATA(0x0); 
    TFT_SEND_DATA(0x16);
    TFT_SEND_DATA(0x08);
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x15);
    TFT_SEND_DATA(0x14);
    TFT_SEND_DATA(0xf); 

    TFT_SEND_CMD(0xF1);             //SET_GAMMA2
        
    TFT_SEND_DATA(0x1f);
    TFT_SEND_DATA(0x41);
    TFT_SEND_DATA(0x1B);
    TFT_SEND_DATA(0x55);
    TFT_SEND_DATA(0x36);
    TFT_SEND_DATA(0x3d);
    TFT_SEND_DATA(0x3e);
    TFT_SEND_DATA(0x0); 
    TFT_SEND_DATA(0x16);
    TFT_SEND_DATA(0x08);
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x15);
    TFT_SEND_DATA(0x14);
    TFT_SEND_DATA(0xf); 

    TFT_SEND_CMD(0xfe);         //关闭Inter register enable
    TFT_SEND_CMD(0xff);

    TFT_SEND_CMD(0x35);         //Tearing Effect Line ON
    TFT_SEND_DATA(0x00);
    TFT_SEND_CMD(0x44);         //Scan line set
    TFT_SEND_DATA(0x00);
    TFT_SEND_CMD(0x11);         //Sleep Out
    delay_ms (120);          //DELAY120ms
    TFT_SEND_CMD(0x29);         //显示开

    TFT_SEND_CMD(0x2A); //Set Column Address 
    TFT_SEND_DATA(0x00);
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x9f); 
    
    TFT_SEND_CMD(0x2B); //Set Page Address 
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x18); 
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x67); 
    TFT_SEND_CMD(0x2c); 
  }
void display_char16_16(unsigned int x,unsigned int y,unsigned long color,const unsigned char *point)
{
   unsigned int column = x+TFT_COLUMN_OFFSET;
  unsigned char tm=0,temp;
   TFT_SEND_CMD(0x2a);    //Column address set
  TFT_SEND_DATA(column>>8);    //start column
  TFT_SEND_DATA(column);
  x=x+15;
    column = x+TFT_COLUMN_OFFSET;
  TFT_SEND_DATA(column>>8);    //start column
  TFT_SEND_DATA(column);

  TFT_SEND_CMD(0x2b);     //Row address set
  TFT_SEND_DATA(0X00);    //start row
  TFT_SEND_DATA(y+TFT_LINE_OFFSET); 
  y=y+15;
  TFT_SEND_DATA(0X00);    //end row
  TFT_SEND_DATA(y+TFT_LINE_OFFSET);
  TFT_SEND_CMD(0x2C);     //Memory write
    
    
  for(column=0;column<32;column++)  //column loop
          {
        temp=*point;
        for(tm=0;tm<8;tm++)
        {
        if(temp&0x01)
          {
 
          TFT_SEND_DATA(color>>8);
          TFT_SEND_DATA(color);
          }
        else 
          {
     
          TFT_SEND_DATA(0);
          TFT_SEND_DATA(0);
          }
          temp>>=1;
        }
        point++;
          
      }
}
void Picture_display(const uint8_t *ptr_pic,uint16_t len)
  {
	TFT_SEND_CMD(0x2a);     //Column address set
  TFT_SEND_DATA(0x00);    //start column
  TFT_SEND_DATA(0x00+TFT_COLUMN_OFFSET); 
  TFT_SEND_DATA(0x00);    //end column
  TFT_SEND_DATA(PIC_LEN-1+ TFT_COLUMN_OFFSET);

  TFT_SEND_CMD(0x2b);     //Row address set
  TFT_SEND_DATA(0x00);    //start row
  TFT_SEND_DATA(0x00+TFT_LINE_OFFSET); 
  TFT_SEND_DATA(0x00);    //end row
  TFT_SEND_DATA(PIC_HIG-1+ TFT_LINE_OFFSET);
  TFT_SEND_CMD(0x2C);     //Memory write
	SPI_CS_0;
	SPI_DC_1;
  HAL_SPI_Transmit_DMA(&hspi1,(uint8_t *)ptr_pic,PIC_HIG*PIC_LEN*2);
 }

void Display_Buffer(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t *bitmap)
  {
	TFT_SEND_CMD(0x2a);     //Column address set
  TFT_SEND_DATA(0x00);    //start column
  TFT_SEND_DATA(x1+TFT_COLUMN_OFFSET); 
  TFT_SEND_DATA(0x00);    //end column
  TFT_SEND_DATA(x2+TFT_COLUMN_OFFSET);

  TFT_SEND_CMD(0x2b);     //Row address set
  TFT_SEND_DATA(0x00);    //start row
  TFT_SEND_DATA(y1+TFT_LINE_OFFSET); 
  TFT_SEND_DATA(0x00);    //end row
  TFT_SEND_DATA(y2+TFT_LINE_OFFSET);
  TFT_SEND_CMD(0x2C);     //Memory write
	SPI_CS_0;
	SPI_DC_1;
  HAL_SPI_Transmit(&hspi1,bitmap,2*(x2-x1+1)*(y2-y1+1),0xFFFF);
		

 }