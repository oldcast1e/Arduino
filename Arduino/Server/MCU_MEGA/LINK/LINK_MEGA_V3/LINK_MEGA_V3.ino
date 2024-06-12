#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

// if the IC model is known or the modules is unreadable, you can use this constructed function
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4); // model,cs,cd,wr,rd,reset

// define some colour values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() {
  Serial.begin(115200);   // initialise serial monitor port
  Serial1.begin(115200);  // initialise Serial1
  Serial.write("Arduino Mega Serial1 test - for loopback test connect pin 18 to pin 19\n");

  // Initialize LCD
  mylcd.Init_LCD();
  Serial.println(mylcd.Read_ID(), HEX);
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Text_Mode(0); // Set text mode
  mylcd.Set_Text_Back_colour(BLACK); // Set background color to black
  mylcd.Set_Text_Size(4); // Set text size to 4
}

void loop() {
  if (Serial1.available()) {
    String inputString = Serial1.readString(); // Read input string from Serial1
    inputString.trim(); // Remove any leading or trailing whitespace
    mylcd.Fill_Screen(BLACK); // Clear screen
    mylcd.Set_Text_colour(WHITE); // Set text color to white
    mylcd.Print_String(inputString.c_str(), 0, 0); // Print the input string at coordinates (0, 0)
  }

  if (Serial.available()) {       // read from Serial output to Serial1
    int inByte = Serial.read();
    Serial1.write(inByte);
  }
}
