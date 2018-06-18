#define ENC_DECODER ENC_FLAKY

#include "ClickEncoder.h"
#include "TimerOne.h"

ClickEncoder *blue;
ClickEncoder *green;
ClickEncoder *yellow;
ClickEncoder *red;

// Encoders have varying numbers of steps per physical "click". 
// 4 is fairly normal.
constexpr int steps_per_notch = 4;

void print_val(ClickEncoder* enc, char name) {
	int value = enc->getValue();
	if (value != 0) {
		Serial.print(name);
		Serial.println(value);
	}

  ClickEncoder::Button b = enc->getButton();
  if (b == ClickEncoder::Pressed || b == ClickEncoder::Released) {
		Serial.print(name);
    switch (b) {
      case ClickEncoder::Pressed: Serial.println("P"); break;
      case ClickEncoder::Released: Serial.println("R"); break;
      default: break;
    }
  }    
}

void setup() {
  Serial.begin(9600);

  blue   = new ClickEncoder(21, 20, 19, steps_per_notch);
  green  = new ClickEncoder(14, 16, 15, steps_per_notch);
  yellow = new ClickEncoder(3, 4, 2, steps_per_notch);
  red    = new ClickEncoder(9, 8, 7, steps_per_notch);

  Timer1.initialize(1000);
  Timer1.attachInterrupt([] {
    blue->service();
    green->service();
    yellow->service();
    red->service();
  }); 
}

void loop() {  
	print_val(blue, 'B');
	print_val(green, 'G');
	print_val(yellow, 'Y');
	print_val(red, 'R');
	delay(10);
}

// vim: ft=cpp

