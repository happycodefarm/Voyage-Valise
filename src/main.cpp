#include <Arduino.h>
#include <ESP32Encoder.h>
#include <BleCombo.h>

ESP32Encoder encoder1;
ESP32Encoder encoder2;

// timer and flag for example, not needed for encoders
unsigned long encoder1lastToggled;
unsigned long encoder2lastToggled;

void setup(){
	Keyboard.begin();
  Mouse.begin();

	Serial.begin(9600);
	// Enable the weak pull down resistors
	ESP32Encoder::useInternalWeakPullResistors=UP;

	// use pin 19 and 18 for the first encoder
	encoder1.attachHalfQuad(26, 25);
	// use pin 17 and 16 for the second encoder
	encoder2.attachHalfQuad(35, 32); // reversed
 
  Serial.println("Starting BLE work!");
  pinMode(LED_BUILTIN, OUTPUT);

  delay(5000);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop(){
  static int32_t encoder1Last = 0;
  static int32_t encoder2Last = 0;

	// Loop and read the count
	//Serial.println("Encoder count = " + String((int32_t)encoder.getCount()) + " " + String((int32_t)encoder2.getCount()));
	
  	Serial.print(encoder1.getCount());
    Serial.print('\t');
    Serial.println(encoder2.getCount());
    
    int32_t dif1 = encoder1.getCount() - encoder1Last;
    int32_t dif2 = encoder2.getCount() - encoder2Last;

    if (dif1 > 0) {
      if (dif2 > 0 ) { // forward
        encoder1Last = encoder1.getCount();
        encoder2Last = encoder2.getCount();
          Keyboard.press(KEY_UP_ARROW);
          delay(100);
          Keyboard.releaseAll();
          if (dif1 > dif2) { // turn left
            Mouse.press(MOUSE_LEFT);
            Mouse.move(100,0);
            Mouse.release(MOUSE_LEFT);
            Mouse.move(-100,0);
          } else if (dif1 < dif2) { // turn right
            Mouse.press(MOUSE_LEFT);
            Mouse.move(-100,0);
            Mouse.release(MOUSE_LEFT);
            Mouse.move(100,0);
          }
      }
    } else if (dif1 < 0) {
      if (dif2 < 0 ) { // forward
        encoder1Last = encoder1.getCount();
        encoder2Last = encoder2.getCount();
          Keyboard.press(KEY_DOWN_ARROW);
          delay(100);
          Keyboard.releaseAll();
          if (dif1 > dif2) { // turn left
            Mouse.press(MOUSE_LEFT);
            Mouse.move(100,0);
            Mouse.release(MOUSE_LEFT);
            Mouse.move(-100,0);
          } else if (dif1 < dif2) { // turn right
            Mouse.press(MOUSE_LEFT);
            Mouse.move(-100,0);
            Mouse.release(MOUSE_LEFT);
            Mouse.move(100,0);
          }
      }
    }

    delay(50);
}