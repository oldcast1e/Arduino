#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

// if the IC model is known or the module is unreadable, you can use this constructed function
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4); // model, cs, cd, wr, rd, reset

#define  BLACK   0x0000

void setup() {
  Serial.begin(9600);
  mylcd.Init_LCD();
  Serial.println(mylcd.Read_ID(), HEX);
  mylcd.Fill_Screen(BLACK);
}

void loop() {
  String inputString = ""; // stores the received string

  // Wait for user input until a newline character is received
  while (!Serial.available()) {
    delay(100);
  }

  // Read serial input until newline character is received
  while (Serial.available()) {
    char inChar = Serial.read();

    // Check for newline character
    if (inChar == '\n') {
      // Print the received string on the TFT screen
      mylcd.Set_Text_Mode(0);
      mylcd.Set_Text_colour(0xFFFF);
      mylcd.Set_Text_Back_colour(BLACK);
      mylcd.Set_Text_Size(1);
      mylcd.Print_String(inputString.c_str(), 0, 0);

      // Clear the input string for the next input
      inputString = "";
    } else {
      // Append the received character to the input string
      inputString += inChar;
    }
  }
}
