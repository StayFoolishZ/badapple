#include "SSD1306.h"
#include <string.h>

unsigned char buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] = {0x00};


void write_data(unsigned char data)
{
	unsigned char bit=0;
	for( bit= 0x80; bit; bit >>= 1) {
    digitalWrite(SCLK,LOW);
    if(data & bit) digitalWrite(SID,HIGH);
    else        digitalWrite(SID,LOW);
	digitalWrite(SCLK,HIGH);
  }
}

void command(unsigned char data)
{
	digitalWrite(CS, HIGH);
    digitalWrite(DC, LOW);
    digitalWrite(CS, LOW);
    write_data(data);
    digitalWrite(CS, HIGH);
}

void init(unsigned int vccstate)
{
	pinMode(SID, OUTPUT);
    pinMode(SCLK, OUTPUT);
    pinMode(DC, OUTPUT);
    pinMode(CS, OUTPUT);
	
	pinMode(RST, OUTPUT);
	digitalWrite(RST, HIGH);
	// VDD (3.3V) goes high at start, lets just chill for a ms
	delay(1);
	// bring reset low
	digitalWrite(RST, LOW);
	// wait 10ms
	delay(10);
	// bring out of reset
	digitalWrite(RST, HIGH);
	
	command(SSD1306_DISPLAYOFF);                    // 0xAE
    command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    command(0x80);                                  // the suggested ratio 0x80
    command(SSD1306_SETMULTIPLEX);                  // 0xA8
    command(0x3F);
    command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    command(0x0);                                   // no offset
    command(SSD1306_SETSTARTLINE | 0x0);            // line #0
    command(SSD1306_CHARGEPUMP);                    // 0x8D
    if (vccstate == SSD1306_EXTERNALVCC) 
      { command(0x10); }
    else 
      { command(0x14); }
    command(SSD1306_MEMORYMODE);                    // 0x20
    command(0x00);                                  // 0x0 act like ks0108
    command(SSD1306_SEGREMAP | 0x1);
    command(SSD1306_COMSCANDEC);
    command(SSD1306_SETCOMPINS);                    // 0xDA
    command(0x12);
    command(SSD1306_SETCONTRAST);                   // 0x81
    if (vccstate == SSD1306_EXTERNALVCC) 
      { command(0x9F); }
    else 
      { command(0xCF); }
    command(SSD1306_SETPRECHARGE);                  // 0xd9
    if (vccstate == SSD1306_EXTERNALVCC) 
      { command(0x22); }
    else 
      { command(0xF1); }
    command(SSD1306_SETVCOMDETECT);                 // 0xDB
    command(0x40);
    command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    command(SSD1306_NORMALDISPLAY);                 // 0xA6
  
	command(SSD1306_DISPLAYON);//--turn on oled panel
}

void display()
{
	command(SSD1306_SETLOWCOLUMN | 0x0);  // low col = 0
	command(SSD1306_SETHIGHCOLUMN | 0x0);  // hi col = 0
	command(SSD1306_SETSTARTLINE | 0x0); // line #0
	
	digitalWrite(CS,HIGH);
	digitalWrite(DC,HIGH);
	digitalWrite(CS,LOW);

	unsigned short i;
    for (i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
      write_data(buffer[i]);
    }
	digitalWrite(CS,HIGH);
}

void draw_pixal(unsigned short x, unsigned short y, unsigned short color)
{
  if ((x < 0) || (x >= 128) || (y < 0) || (y >= 64))
    return;
  if (color == WHITE) 
    buffer[x+ (y/8)*SSD1306_LCDWIDTH] |= _BV((y%8));  
  else
    buffer[x+ (y/8)*SSD1306_LCDWIDTH] &= ~_BV((y%8)); 
}

void draw_bitmap(short x,short y,const unsigned char *bitmap,short w,short h,unsigned short color) {

  short i, j, byteWidth = (w + 7) / 8;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
		draw_pixal(x+i, y+j, color);
      }
    }
  }
}

void clear_screen()
{
  memset(buffer,0,SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8);
}
