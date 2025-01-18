/***********************************************************************************
*This program is a demo of how to display pictures and 
*how to use the rotate function to display strings.
*This demo was made for LCD modules with an 8bit data port.
*This program requires the LCDWIKI library.

* File                : display_graphics_mega.ino
* Hardware Environment: Arduino Mega2560
* Build Environment   : Arduino

*Set the pins to the correct ones for your development shield or breakout board.
*This demo uses the BREAKOUT BOARD only and these 8bit data lines to the LCD:
*Pin usage as follows:
*
*                  LCD_CS  LCD_CD  LCD_WR  LCD_RD  LCD_RST
*Arduino Mega2560    A3      A2      A1      A0      A4
*
*                  LCD_D0  LCD_D1  LCD_D2  LCD_D3  LCD_D4  LCD_D5  LCD_D6  LCD_D7
*Arduino Mega2560    8       9       2       3       4       5       6       7
*
*Remember to set the pins to suit your display module!
*
* @attention
*
* THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY AND AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER TO SAVE TIME.
* AS A RESULT, QD ELECTRONIC SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/

#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library

// LCD configuration for Mega2560 (model, cs, cd, wr, rd, reset)
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

// Define color values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Clear the screen with different colors
void fill_screen_test()
{
  mylcd.Fill_Screen(BLACK);  
  mylcd.Fill_Screen(RED);
  mylcd.Fill_Screen(GREEN);
  mylcd.Fill_Screen(BLUE);
  mylcd.Fill_Screen(BLACK);
}

// Display strings
void text_test()
{
  mylcd.Set_Text_Mode(0);
  
  mylcd.Fill_Screen(BLACK);  
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Hello World!", 0, 0);
  
  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Size(2);
  mylcd.Print_Number_Float(1234.56, 2, 0, 8, '.', 0, ' ');
  
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Size(3);
  mylcd.Print_Number_Int(0xDEADBEF, 0, 24, 0, ' ', 16); 

  mylcd.Set_Text_colour(GREEN);
  mylcd.Set_Text_Size(5);  
  mylcd.Print_String("Arduino Mega", 0, 56); 
}

// Draw lines
void lines_test()
{
    mylcd.Fill_Screen(BLACK);
    mylcd.Set_Draw_color(GREEN);
    for (int i = 0; i < mylcd.Get_Display_Width(); i += 5)
    {
        mylcd.Draw_Line(0, 0, i, mylcd.Get_Display_Height() - 1);
    }
    for (int i = mylcd.Get_Display_Height() - 1; i >= 0; i -= 5)
    {
        mylcd.Draw_Line(0, 0, mylcd.Get_Display_Width() - 1, i);
    }
}

// Draw rectangles
void rectangle_test()
{
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(GREEN);
  for (int i = 0; i < mylcd.Get_Display_Width() / 2; i += 4)
  {
    mylcd.Draw_Rectangle(i, i, mylcd.Get_Display_Width() - 1 - i, mylcd.Get_Display_Height() - 1 - i);
    delay(5);
  }
}

// Draw and fill circles
void fill_circles_test()
{
  int r = 10;
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(MAGENTA);
  for (int i = r; i < mylcd.Get_Display_Width(); i += 2 * r)
  {
    for (int j = r; j < mylcd.Get_Display_Height(); j += 2 * r)
    {
      mylcd.Fill_Circle(i, j, r);
    }
  }
}

// Setup function to initialize the LCD and run all tests
void setup() 
{
  Serial.begin(9600);
  mylcd.Init_LCD();
  Serial.println(mylcd.Read_ID(), HEX);

  fill_screen_test();
  delay(500);
  text_test();
  delay(500);
  lines_test();
  delay(500);
  rectangle_test();
  delay(500);
  fill_circles_test();
  delay(3000);
}

// Loop function to demonstrate screen rotation
void loop() 
{
  for (uint8_t rotation = 0; rotation < 4; rotation++) 
  {
    mylcd.Set_Rotation(rotation);
    text_test();
    delay(2000);
  }
}
