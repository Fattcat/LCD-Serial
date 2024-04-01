#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// VCC - 5V
// GND - GND
// SCL - A4 
// SDA - A5

// Set the LCD address to 0x27 or 0x3F for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);  

unsigned long lastMessageTime = 0;
const unsigned long displayClearDelay = 15000; // 15 seconds

void setup() {
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
  // Set up serial communication
  Serial.begin(9600);
}

void loop() {
  // Check if there's data available to read from serial monitor
  if (Serial.available() > 0) {
    // Read the data from serial monitor
    String message = Serial.readStringUntil('\n'); // Read until newline character
    // Check if the message is "clear"
    if (message == "vycistiMa") {
      lcd.clear(); // for Clear the LCD
      Serial.print("Displej bol vycisteny.");
    } else {
      // Clear the LCD
      lcd.clear();
      // Print the message on the LCD
      int charIndex = 0;
      int line = 0;
      while (charIndex < message.length()) {
        // Print a substring of the message that fits on one line
        lcd.setCursor(0, line);
        lcd.print(message.substring(charIndex, min(charIndex + 20, message.length())));
        // Move to the next line
        line++;
        // Move to the next substring of the message
        charIndex += 20;
        // If there are more lines to print and we've reached the end of the screen, reset to the beginning
        if (line >= 4) {
          charIndex = 0;
          line = 0;
        }
      }
    }
    // Update the last message time
    lastMessageTime = millis();
  }

  // Check if it's time to clear the display
  if (millis() - lastMessageTime >= displayClearDelay) {
    // Clear the LCD
    lcd.clear();
    // Reset the last message time
    lastMessageTime = millis();
  }
}
